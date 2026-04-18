import re

with open('src/strings.c', 'r', encoding='utf-8') as f:
    lines = f.readlines()

count = 0
for line in lines:
    match = re.search(r'_\("(.*?)"\)', line)
    if match:
        text = match.group(1)
        # Check if text contains any lowercase letters (meaning it's not ALL CAPS)
        if any(c.islower() for c in text):
            count += 1

print(f"Lines to translate: {count}")

