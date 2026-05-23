import json
import re

log_path = "/home/george/.gemini/antigravity/brain/085746ce-6729-46d1-a2dd-1bd5bcc29cfc/.system_generated/logs/overview.txt"
tv_path = "/home/george/Dev/pokeemerald-greeklish/data/text/tv.inc"

# Read original tv.inc
with open(tv_path, "r", encoding="utf-8") as f:
    tv_lines = f.readlines()

replacements = []

with open(log_path, "r", encoding="utf-8") as f:
    for line in f:
        try:
            data = json.loads(line)
            if data.get("source") == "MODEL" and data.get("type") == "PLANNER_RESPONSE":
                tcalls = data.get("tool_calls", [])
                for tc in tcalls:
                    if tc.get("name") == "replace_file_content":
                        args = tc.get("args", {})
                        if "tv.inc" in args.get("TargetFile", ""):
                            start = int(args.get("StartLine"))
                            end = int(args.get("EndLine"))
                            target = args.get("TargetContent")
                            replacement = args.get("ReplacementContent")
                            
                            replacements.append({
                                "start": start,
                                "end": end,
                                "target": target,
                                "replacement": replacement
                            })
        except Exception as e:
            pass

print(f"Found {len(replacements)} replacements in logs.")

current_content = "".join(tv_lines)

for rep in replacements:
    target = rep["target"]
    replacement = rep["replacement"]
    
    # Try finding exact target content
    if target in current_content:
        current_content = current_content.replace(target, replacement)
        print(f"Applied replacement of length {len(replacement)} via exact match.")
    else:
        print(f"Could not apply replacement starting with: {target[:50]}...")

# Write back to tv.inc
with open(tv_path, "w", encoding="utf-8") as f:
    f.write(current_content)

print("Restoration complete.")
