import os
import glob
import time
import re
import traceback
import json

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

system_prompt = """You are a professional translator working on a Pokémon emerald ROM hack.
You are tasked with translating in-game dialogs from English to Greek alphabet.
Follow these rules strictly:
1. Return ONLY valid JSON in the exact same format as the input. The input is a list of objects with 'id' and 'text'. You must return a list of objects with 'id' and the translated 'text'.
2. Keep the exact assembly format: `.string "..."`. Replicate all formatting tokens exactly as they appear: \\n, \\l, \\p, and $.
3. Do NOT exceed 39 characters of text per line (excluding the control characters \\n \\l \\p $ and the `.string "` wrapper). 
   - E.g. .string "123456789012345678901234567890123456789" is max length.
4. Keep all uppercase names and tags in English (e.g. {PLAYER}, DAN, KIRA, TRAINER, POKéMON).
5. IMPORTANT: Use completely gender-neutral language when referring to the player (e.g. {PLAYER}). Do not use masculine or feminine modifiers (like έναν vs μία) if referring to {PLAYER}. Substitute with phrases that are gender neutral in Greek.
6. Translate to Greek text (using Greek characters, not Greeklish), except for terms specified to remain in English.
"""

model = genai.GenerativeModel(
    'gemini-2.5-flash',
    system_instruction=system_prompt,
    generation_config=genai.types.GenerationConfig(
        response_mime_type="application/json",
    )
)

def translate_blocks_batch(blocks):
    if not blocks: return {}
    input_data = [{"id": b['batch_id'], "text": '\n'.join(b['lines'])} for b in blocks]
    input_json = json.dumps(input_data)
    
    max_retries = 5
    for attempt in range(max_retries):
        try:
            response = model.generate_content(input_json)
            result = json.loads(response.text)
            output_map = {item['id']: item['text'] for item in result}
            return output_map
        except Exception as e:
            error_str = str(e).lower()
            if "429" in error_str or "quota" in error_str or "exhausted" in error_str:
                print(f"    [!] Rate limit hit! Sleeping for 65 seconds... (Attempt {attempt+1}/{max_retries})")
                print(f"        (Note: Gemini Free-Tier has a 1500 Requests/Day and 15 Requests/Minute Limit).")
                time.sleep(65)
            else:
                print(f"    [!] API Error/JSON parse (attempt {attempt+1}/{max_retries}): {e}")
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
        return 
        
    pending_blocks = []
    index = 0
    for b in blocks_to_translate:
        original_text = '\n'.join(b['lines'])
        if not re.search(r'[α-ωΑ-Ω]', original_text):
            b['batch_id'] = index
            pending_blocks.append(b)
            index += 1
            
    if not pending_blocks:
        return

    print(f"  -> Batch translating {len(pending_blocks)} blocks in {file_path}...")
    translated_map = translate_blocks_batch(pending_blocks)
    
    if not translated_map:
        print("  [!] Failed batch translation.")
        return
        
    pending_blocks.sort(key=lambda x: x['start'], reverse=True)
    
    changed = False
    for block in pending_blocks:
        b_id = block['batch_id']
        if b_id in translated_map:
            translated_text = translated_map[b_id]
            new_lines = translated_text.split('\n')
            
            indent_match = re.match(r'^([ \t]*)', block['lines'][0])
            indent = indent_match.group(1) if indent_match else '\t'
            
            new_lines = [f"{indent}{line.strip()}" for line in new_lines if line.strip().startswith('.string')]
            
            if new_lines:
                lines[block['start']:block['end']] = new_lines
                changed = True
                
    if changed:
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write('\n'.join(lines))
        print(f"  [+] Updated {file_path}")

def main():
    search_path = os.path.join("data", "maps", "**", "scripts.inc")
    all_files = glob.glob(search_path, recursive=True)
    all_files = sorted(all_files, key=lambda x: x.split(os.sep)[-2] if len(x.split(os.sep)) >= 2 else x)
    
    target_files = []
    for f in all_files:
        parts = f.split(os.sep)
        if len(parts) >= 2:
            dir_name = parts[-2]
            if dir_name <= "BattleFrontier_ExchangeServiceCorner":
                target_files.append(f)
                
    print(f"Starting targeted translation across {len(target_files)} files.")
    
    for i, file_path in enumerate(target_files):
        print(f"[{i+1}/{len(target_files)}] Checking {file_path}...")
        process_file(file_path)
        time.sleep(2)
        
    print("\nTargeted translation script completed!")

if __name__ == "__main__":
    main()
