import os
import glob
import time
import re
import traceback

try:
    import google.generativeai as genai
except ImportError:
    print("Error: The 'google-generativeai' package is not installed.")
    print("Please install it using: pip install google-generativeai")
    exit(1)

try:
    from dotenv import load_dotenv
    load_dotenv() # Loads variables from .env file into os.environ
except ImportError:
    print("Notice: 'python-dotenv' is not installed. If using a .env file, please run: pip install python-dotenv")

API_KEY = os.environ.get("GEMINI_API_KEY")
if not API_KEY:
    print("Error: GEMINI_API_KEY is not set.")
    print("Please create a .env file securely containing: GEMINI_API_KEY=your_api_key_here")
    exit(1)

genai.configure(api_key=API_KEY)

# Use gemini-1.5-flash as it's the fastest and most cost-effective for large batch tasks
system_prompt = """You are a professional translator working on a Pokémon emerald ROM hack.
You are tasked with translating in-game dialogs from English to Greek.
Follow these rules strictly:
1. Keep the exact assembly format. E.g.
   .string "..."
2. Replicate all formatting tokens exactly as they appear: \\n (newline), \\l (scroll line), \\p (paragraph), and $ (end of string).
3. Do NOT exceed 39 characters of text per line (excluding the control characters \\n \\l \\p $ and the `.string \"` wrapper).
4. Keep all uppercase names and tags in English (e.g. {PLAYER}, MOM, RIVAL, PROF. BIRCH, POKéMON).
5. Output ONLY the translated assembly code blocks. No markdown block wrappings (```) around your response.
"""

model = genai.GenerativeModel(
    'gemini-2.5-flash',
    system_instruction=system_prompt
)

def translate_block(block_text):
    max_retries = 5
    for attempt in range(max_retries):
        try:
            response = model.generate_content(block_text)
            text = response.text.strip()
            # Remove any markdown wrapping the model might add by mistake
            if text.startswith('```'):
                text = re.sub(r'^```[\w]*\n', '', text)
                text = re.sub(r'\n```$', '', text)
            return text
        except Exception as e:
            error_str = str(e).lower()
            if "429" in error_str or "quota" in error_str or "exhausted" in error_str:
                print(f"    [!] Rate limit hit! Sleeping for 65 seconds... (Attempt {attempt+1}/{max_retries})")
                print(f"        (Note: Gemini Free-Tier has a 1500 Requests/Day and 15 Requests/Minute Limit).")
                time.sleep(65)
            else:
                print(f"    [!] API Error (attempt {attempt+1}/{max_retries}): {e}")
                time.sleep(10)
    return None

def process_file(file_path):
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    lines = content.split('\n')
    blocks_to_translate = []
    
    in_string_block = False
    current_block = []
    start_idx = -1
    
    # Identify contiguous blocks of .string directives
    for i, line in enumerate(lines):
        if re.match(r'^[ \t]*\.string[ \t]+".*"', line):
            if not in_string_block:
                in_string_block = True
                start_idx = i
            current_block.append(line)
        else:
            if in_string_block:
                blocks_to_translate.append({'start': start_idx, 'end': i, 'lines': current_block})
                in_string_block = False
                current_block = []
                
    if in_string_block:
        blocks_to_translate.append({'start': start_idx, 'end': len(lines), 'lines': current_block})
        
    if not blocks_to_translate:
        return # Skip file if no strings match
        
    # Process from bottom to top so index replacements don't shift prior indices
    blocks_to_translate.reverse()
    
    changed = False
    for block in blocks_to_translate:
        original_text = '\n'.join(block['lines'])
        
        # Skip this block if it already contains Greek characters (makes script resumable)
        if re.search(r'[α-ωΑ-Ω]', original_text):
            continue
            
        print(f"  -> Translating block at line {block['start']} ({len(block['lines'])} lines)...")
        translated_text = translate_block(original_text)
        
        if translated_text:
            new_lines = translated_text.split('\n')
            # Fix indentation to match the original block's first line
            indent_match = re.match(r'^([ \t]*)', block['lines'][0])
            indent = indent_match.group(1) if indent_match else '\t'
            
            # Apply indentation and clean any accidental empty lines
            new_lines = [f"{indent}{line.strip()}" for line in new_lines if line.strip().startswith('.string')]
            
            if new_lines:
                lines[block['start']:block['end']] = new_lines
                changed = True
                
            # Strictly pad spacing to ~5 seconds per request to abide by the free-tier limit of 15 Requests Per Minute
            time.sleep(5)
        else:
            print(f"    [!] Failed to translate block at line {block['start']}. Keeping original.")

    if changed:
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write('\n'.join(lines))
        print(f"  [+] Updated {file_path}")

def main():
    search_path = os.path.join("data", "maps", "**", "scripts.inc")
    files = glob.glob(search_path, recursive=True)
    
    print(f"Starting translation automation across {len(files)} potential files.")
    print("Note: The script safely skips already-translated blocks, so you can stop and resume it at any time.")
    
    for i, file_path in enumerate(files):
        print(f"[{i+1}/{len(files)}] Checking {file_path}...")
        process_file(file_path)
        
    print("\nTranslation script completed!")

if __name__ == "__main__":
    main()
