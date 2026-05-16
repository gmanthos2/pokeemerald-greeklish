import re

def check_line_lengths(filename):
    with open(filename, 'r', encoding='utf-8') as f:
        lines = f.readlines()
    
    for i, line in enumerate(lines):
        match = re.search(r'\.string "(.*)"', line)
        if match:
            content = match.group(1)
            # Remove control characters like \n, \p, \l, \c, \r
            # and macros like {STR_VAR_1}, {PLAYER}
            clean_content = re.sub(r'\\[nplcr]', '', content)
            clean_content = re.sub(r'\{[A-Z0-9_]+\}', 'XXXXXXXXXX', clean_content) # Placeholder for macros
            
            # The length check is tricky because macros can have variable lengths.
            # But usually we assume a reasonable length for macros.
            # Let's just check the length of the string without macros first.
            raw_len = len(re.sub(r'\{[A-Z0-9_]+\}', '', clean_content))
            # POKéMON is 7 chars. PLAYER is 7-8 chars.
            # If we assume 10 chars per macro:
            macro_count = len(re.findall(r'\{[A-Z0-9_]+\}', clean_content))
            total_estimated_len = raw_len + (macro_count * 10) # 10 is a safe bet for POKéMON/PLAYER
            
            if total_estimated_len > 39:
                print(f"Line {i+1} might be too long ({total_estimated_len} chars): {content}")

if __name__ == "__main__":
    check_line_lengths("data/text/apprentice.inc")
