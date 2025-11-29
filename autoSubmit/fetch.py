import os
import sys
import time
import json
import requests
from google import genai

class CodeforcesFetcher:
    def __init__(self, config_file='cf_config.json'):
        self.config = self.load_config(config_file)
        
        self.api_key = os.getenv('GEMINI_API_KEY')
        if not self.api_key:
            print("❌ GEMINI_API_KEY not set")
            sys.exit(1)
        
        self.client = genai.Client(api_key=self.api_key)
        
    def load_config(self, config_file):
        if not os.path.exists(config_file):
            print(f"Config file {config_file} not found")
            sys.exit(1)
        
        with open(config_file, 'r') as f:
            return json.load(f)
    
    def get_problems_by_rating(self, ratings=[800, 900], limit=50):
        url = "https://codeforces.com/api/problemset.problems"
        response = requests.get(url, timeout=10)
        data = response.json()
        
        if data['status'] != 'OK':
            return []
        
        problems = []
        for problem in data['result']['problems']:
            if 'rating' in problem and problem['rating'] in ratings:
                problems.append({
                    'code': f"{problem['contestId']}{problem['index']}",
                    'contest_id': problem['contestId'],
                    'index': problem['index'],
                    'name': problem['name'],
                    'rating': problem['rating'],
                    'tags': problem.get('tags', [])
                })
        
        return problems[:limit]
    
    def generate_solution(self, problem):
        url = f"https://codeforces.com/problemset/problem/{problem['contest_id']}/{problem['index']}"
        tags_str = ', '.join(problem['tags']) if problem['tags'] else 'None'
        
        prompt = f"""Solve this competitive programming problem from Codeforces.

Problem: {problem['code']} - {problem['name']}
Rating: {problem['rating']}
Tags: {tags_str}
URL: {url}

Generate a COMPLETE working C++ solution that:
- Handles all edge cases
- Uses efficient algorithms
- Includes fast I/O
- Uses #include <bits/stdc++.h>
- Solves the problem correctly

CRITICAL: Provide ONLY the raw C++ code. No explanations, no markdown blocks, no formatting. Just pure C++ code starting with #include and ending with the closing brace of main().
"""

        try:
            response = self.client.models.generate_content(
                model="gemini-3-pro-preview",
                contents=prompt
            )
            
            code = response.text.strip()
            
            lines = code.split('\n')
            code_lines = []
            in_code = False
            
            for line in lines:
                if '```' in line:
                    in_code = not in_code
                    continue
                if in_code or '#include' in line or (code_lines and line.strip()):
                    code_lines.append(line)
            
            code = '\n'.join(code_lines).strip()
            
            if '#include' in code and 'main' in code:
                return code
            
            return None
                
        except Exception as e:
            print(f"  AI error: {e}")
            return None
    
    def save_problem(self, problem, code):
        folder = self.config['code_folder']
        os.makedirs(folder, exist_ok=True)
        
        filename = f"{problem['code']}.cpp"
        filepath = os.path.join(folder, filename)
        
        if os.path.exists(filepath):
            print(f"  ⚠ Exists")
            return False
        
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(code)
        
        print(f"  ✓ Saved")
        return True
    
    def fetch_and_save_problems(self, ratings=[800, 900], max_problems=50):
        print("="*60)
        print(f"Fetching {max_problems} problems (ratings: {ratings})")
        print("="*60)
        
        problems = self.get_problems_by_rating(ratings, max_problems)
        
        if not problems:
            print("No problems found")
            return
        
        print(f"Found {len(problems)} problems\n")
        input("Press Enter to start...")
        
        saved = 0
        skipped = 0
        failed = 0
        
        for i, problem in enumerate(problems, 1):
            print(f"\n[{i}/{len(problems)}] {problem['code']} - {problem['name']}")
            
            code = self.generate_solution(problem)
            
            if not code:
                print(f"  ✗ Failed")
                failed += 1
                continue
            
            if self.save_problem(problem, code):
                saved += 1
            else:
                skipped += 1
            
            if i < len(problems):
                time.sleep(2)
        
        print("\n" + "="*60)
        print(f"✓ Saved: {saved}")
        print(f"⚠ Skipped: {skipped}")
        print(f"✗ Failed: {failed}")
        print(f"📁 {self.config['code_folder']}")
        print("="*60)

if __name__ == "__main__":
    max_problems = 50
    
    if len(sys.argv) > 1:
        try:
            max_problems = int(sys.argv[1])
        except:
            print("Usage: python fetch.py [count]")
            sys.exit(1)
    
    fetcher = CodeforcesFetcher()
    fetcher.fetch_and_save_problems(max_problems=max_problems)