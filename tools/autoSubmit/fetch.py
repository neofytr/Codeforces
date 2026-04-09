import os
import sys
import json
from pathlib import Path
from google import genai
import base64

class CodeforcesFetcher:
    def __init__(self, config_file='cf_config.json'):
        with open(config_file, 'r') as f:
            self.config = json.load(f)
        
        self.api_key = os.getenv('GEMINI_API_KEY')
        if not self.api_key:
            print("❌ GEMINI_API_KEY not set")
            sys.exit(1)
        
        self.client = genai.Client(api_key=self.api_key)
        self.problems_dir = Path('problems')
        self.solutions_dir = Path(self.config['code_folder'])
        
    def find_problem_a_pdfs(self, limit):
        pdfs = []
        
        for range_folder in sorted(self.problems_dir.iterdir()):
            if not range_folder.is_dir() or range_folder.name in ['LICENSE', 'README.md']:
                continue
            
            for contest_folder in sorted(range_folder.iterdir(), key=lambda x: int(x.name) if x.name.isdigit() else 999999):
                if not contest_folder.is_dir():
                    continue
                
                contest_num = contest_folder.name
                a_pdf = contest_folder / f"{contest_num}A.pdf"
                
                if a_pdf.exists():
                    pdfs.append({
                        'pdf_path': a_pdf,
                        'contest': contest_num,
                        'code': f"{contest_num}A"
                    })
                    
                    if len(pdfs) >= limit:
                        return pdfs
        
        return pdfs
    
    def generate_solution_from_pdf(self, pdf_path):
        with open(pdf_path, 'rb') as f:
            pdf_data = f.read()
        
        pdf_base64 = base64.b64encode(pdf_data).decode('utf-8')
        
        prompt = """Read this Codeforces problem PDF and solve it.

Generate a COMPLETE working C++ solution that:
- Solves the problem correctly
- Handles all edge cases
- Uses #include <bits/stdc++.h>
- Uses fast I/O

Return ONLY raw C++ code. No explanations, no markdown, no backticks."""

        try:
            response = self.client.models.generate_content(
                model="gemini-2.5-flash",
                contents=[
                    {
                        "role": "user",
                        "parts": [
                            {"text": prompt},
                            {
                                "inline_data": {
                                    "mime_type": "application/pdf",
                                    "data": pdf_base64
                                }
                            }
                        ]
                    }
                ]
            )
            
            code = response.text.strip()
            
            if '```' in code:
                lines = code.split('\n')
                code_lines = []
                in_code = False
                
                for line in lines:
                    if '```' in line:
                        in_code = not in_code
                        continue
                    if in_code:
                        code_lines.append(line)
                
                code = '\n'.join(code_lines).strip()
            
            if '#include' in code and 'main' in code:
                return code
            
            return None
                
        except Exception as e:
            print(f"  ✗ Error: {e}")
            return None
    
    def save_solution(self, code, problem_code):
        self.solutions_dir.mkdir(exist_ok=True)
        
        filepath = self.solutions_dir / f"{problem_code}.cpp"
        
        if filepath.exists():
            return False
        
        with open(filepath, 'w') as f:
            f.write(code)
        
        return True
    
    def run(self, limit=50):
        print(f"Finding first {limit} problem A PDFs...")
        
        pdfs = self.find_problem_a_pdfs(limit)
        
        if not pdfs:
            print("No PDFs found")
            return
        
        print(f"Found {len(pdfs)} PDFs\n")
        
        saved = 0
        skipped = 0
        failed = 0
        
        for i, problem in enumerate(pdfs, 1):
            print(f"[{i}/{len(pdfs)}] {problem['code']}", end=' ', flush=True)
            
            code = self.generate_solution_from_pdf(problem['pdf_path'])
            
            if not code:
                print("✗")
                failed += 1
                continue
            
            if self.save_solution(code, problem['code']):
                print("✓")
                saved += 1
            else:
                print("⚠")
                skipped += 1
        
        print(f"\n✓ Saved: {saved} | ⚠ Skipped: {skipped} | ✗ Failed: {failed}")

if __name__ == "__main__":
    limit = 50
    
    if len(sys.argv) > 1:
        limit = int(sys.argv[1])
    
    fetcher = CodeforcesFetcher()
    fetcher.run(limit)