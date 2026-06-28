from pathlib import Path

# ==========================
# Paths
# ==========================

project_root = Path(__file__).parent.parent

html_file = project_root / "Web_UI" / "index.html"
css_file = project_root / "Web_UI" / "style.css"
js_file = project_root / "Web_UI" / "script.js"

output_file = project_root / "Firmware" / "webpage.h"

# ==========================
# Read Files
# ==========================

html = html_file.read_text(encoding="utf-8")
css = css_file.read_text(encoding="utf-8")
js = js_file.read_text(encoding="utf-8")

# ==========================
# Embed CSS
# ==========================

html = html.replace(
    '<link rel="stylesheet" href="style.css">',
    f"<style>\n{css}\n</style>"
)

# ==========================
# Embed JS
# ==========================

html = html.replace(
    '<script src="script.js"></script>',
    f"<script>\n{js}\n</script>"
)

# ==========================
# Create webpage.h
# ==========================

header = f'''#ifndef WEBPAGE_H
#define WEBPAGE_H

const char webpage[] PROGMEM = R"rawliteral(
{html}
)rawliteral";

#endif
'''

output_file.write_text(header, encoding="utf-8")

print("===================================")
print("webpage.h generated successfully!")
print(output_file)
print("===================================")
