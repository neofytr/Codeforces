import os
import sys
import time
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.support.ui import Select
import json
from pathlib import Path
from google import genai
import base64

class CodeforcesSubmitter:
    def __init__(self, config_file='cf_config.json'):
        self.config = self.load_config(config_file)
        self.driver = None
        
    def load_config(self, config_file):
        if not os.path.exists(config_file):
            template = {
                "code_folder": "/path/to/your/code/folder",
                "random_folder": "~/Desktop/Codeforces/random",
                "debug_port": 9222
            }
            with open(config_file, 'w') as f:
                json.dump(template, f, indent=4)
            print(f"Edit {config_file} with:")
            print("1. code_folder: where your .cpp files are")
            print("2. random_folder: folder with random solutions")
            print("3. debug_port: usually 9222 (default is fine)")
            sys.exit(1)
        
        with open(config_file, 'r') as f:
            return json.load(f)
    
    def init_driver(self):
        """Connect to already-running Chrome with remote debugging"""
        debug_port = self.config.get('debug_port', 9222)
        
        options = webdriver.ChromeOptions()
        options.add_experimental_option("debuggerAddress", f"127.0.0.1:{debug_port}")
        
        print(f"Connecting to Chrome on port {debug_port}...")
        print("\nIf you get an error, start Chrome with:")
        print(f"  google-chrome --remote-debugging-port={debug_port}")
        print("  (or use the start_chrome.sh script)\n")
        
        try:
            self.driver = webdriver.Chrome(options=options)
            print("✓ Connected to existing Chrome session")
        except Exception as e:
            print(f"✗ Error: {e}")
            print("\nSteps to fix:")
            print(f"1. Close all Chrome windows")
            print(f"2. Start Chrome with: google-chrome --remote-debugging-port={debug_port}")
            print(f"3. Login to Codeforces in that window")
            print(f"4. Run this script again")
            sys.exit(1)
    
    def check_login(self):
        """Check if logged into Codeforces"""
        print("Checking login status...")
        
        # Don't navigate if already on Codeforces
        current_url = self.driver.current_url
        if "codeforces.com" not in current_url:
            self.driver.get("https://codeforces.com")
            time.sleep(2)
        
        if "logout" in self.driver.page_source.lower():
            print("✓ Already logged in")
            return True
        else:
            print("✗ Not logged in to Codeforces")
            print("Please login in the browser window and press Enter...")
            input()
            
            self.driver.refresh()
            time.sleep(2)
            
            if "logout" in self.driver.page_source.lower():
                print("✓ Login confirmed")
                return True
            else:
                print("✗ Still not logged in. Exiting.")
                return False
    
    def find_code_file(self, problem_code):
        """Find the code file for the problem"""
        folder = self.config['code_folder']
        exact_file = os.path.join(folder, f"{problem_code}.cpp")
        
        if os.path.exists(exact_file):
            return exact_file
        
        # Try case-insensitive search
        for file in os.listdir(folder):
            if file.lower() == f"{problem_code.lower()}.cpp":
                return os.path.join(folder, file)
        
        print(f"✗ File {problem_code}.cpp not found in {folder}")
        return None
    
    def identify_problem_with_gemini(self, file_path, filename):
        """Use Gemini with search to identify the problem code from filename"""
        api_key = os.getenv('GEMINI_API_KEY')
        if not api_key:
            print("  ⚠ GEMINI_API_KEY not set, skipping AI identification")
            return None
        
        try:
            client = genai.Client(api_key=api_key)
            
            prompt = f"""Search for "{filename} codeforces" and find the Codeforces problem code.

The problem code format is: CONTESTNUMBER + LETTER (e.g., 1234A, 567B, 2167C)

Search the web and find which Codeforces problem this filename refers to.
Respond with ONLY the problem code in format like "1234A". Nothing else, no explanation."""

            response = client.models.generate_content(
                model="gemini-2.0-flash-exp",
                contents=prompt,
                config={
                    'tools': [{'google_search': {}}]
                }
            )
            
            problem_code = response.text.strip()
            
            # Clean up response - remove any extra text
            # Look for pattern like 1234A
            import re
            match = re.search(r'\b(\d{3,4}[A-Z])\b', problem_code)
            if match:
                return match.group(1)
            
            # Validate format: digits + letter
            if problem_code and len(problem_code) >= 2:
                has_digits = any(c.isdigit() for c in problem_code)
                has_letter = any(c.isalpha() for c in problem_code)
                if has_digits and has_letter:
                    return problem_code
            
            return None
            
        except Exception as e:
            print(f"  ⚠ Gemini error: {e}")
            return None
    
    def submit_code(self, problem_code, file_path):
        """Submit the code to Codeforces"""
        contest_id = ''.join(filter(str.isdigit, problem_code))
        problem_letter = ''.join(filter(str.isalpha, problem_code))
        
        submit_url = f"https://codeforces.com/problemset/submit/{contest_id}/{problem_letter}"
        print(f"Opening: {submit_url}")
        
        self.driver.get(submit_url)
        time.sleep(3)
        
        try:
            # Read the code
            with open(file_path, 'r', encoding='utf-8') as f:
                code = f.read()
            
            # Select compiler
            print("Selecting compiler...")
            lang_select = Select(WebDriverWait(self.driver, 10).until(
                EC.presence_of_element_located((By.NAME, "programTypeId"))
            ))
            
            # Try to select G++20
            try:
                lang_select.select_by_visible_text("GNU G++20 13.2 (64 bit, winlibs)")
                print("Selected: GNU G++20")
            except:
                for option in lang_select.options:
                    if "G++20" in option.text or "G++17" in option.text:
                        lang_select.select_by_visible_text(option.text)
                        print(f"Selected: {option.text}")
                        break
            
            # Insert code
            print("Inserting code...")
            code_area = self.driver.find_element(By.ID, "sourceCodeTextarea")
            self.driver.execute_script("arguments[0].value = arguments[1];", code_area, code)
            
            time.sleep(1)
            
            # Submit
            print("Submitting...")
            submit_button = self.driver.find_element(By.CLASS_NAME, "submit")
            submit_button.click()
            
            time.sleep(3)
            print(f"✓ Submitted {problem_code}")
            
            # Navigate to submissions
            print("Opening your submissions...")
            try:
                # Try to extract handle from URL or page
                if "/profile/" in self.driver.current_url:
                    handle = self.driver.current_url.split("/profile/")[1].split("/")[0]
                else:
                    # Try to find handle from the page
                    handle_elem = self.driver.find_element(By.CSS_SELECTOR, "a[href*='/profile/']")
                    handle = handle_elem.get_attribute("href").split("/profile/")[1].split("/")[0]
                
                self.driver.get(f"https://codeforces.com/submissions/{handle}")
            except:
                print("(Couldn't auto-navigate to submissions)")
            
            return True
            
        except Exception as e:
            print(f"✗ Error during submission: {e}")
            import traceback
            traceback.print_exc()
            return False
    
    def run(self, problem_code):
        """Main execution flow"""
        try:
            # Find the code file
            file_path = self.find_code_file(problem_code)
            if not file_path:
                return
            
            print(f"✓ Found: {file_path}")
            
            # Connect to existing Chrome
            self.init_driver()
            
            # Verify login
            if not self.check_login():
                return
            
            # Submit
            if self.submit_code(problem_code, file_path):
                print("\n" + "="*50)
                print("✓ Submission complete!")
                print("Check the browser for verdict")
                print("="*50)
                print("\nLeaving browser open for you to check results...")
                print("Press Enter to close the script (browser will stay open)...")
                input()
            
        except KeyboardInterrupt:
            print("\n\nInterrupted by user")
        except Exception as e:
            print(f"Unexpected error: {e}")
            import traceback
            traceback.print_exc()
        finally:
            # Don't close the driver - let the user's Chrome stay open
            print("Browser will remain open")

    def submit_all(self):
        """Submit all .cpp files in the code folder"""
        folder = self.config['code_folder']
        cpp_files = [f for f in os.listdir(folder) if f.endswith('.cpp')]
        
        if not cpp_files:
            print(f"No .cpp files found in {folder}")
            return
        
        print(f"Found {len(cpp_files)} files to submit:")
        for f in cpp_files:
            print(f"  - {f}")
        
        print("\nStarting submissions...")        
        self.init_driver()
        
        if not self.check_login():
            return
        
        success = 0
        failed = 0
        
        for cpp_file in cpp_files:
            problem_code = cpp_file[:-4]  # Remove .cpp extension
            file_path = os.path.join(folder, cpp_file)
            
            print(f"\n{'='*50}")
            print(f"Submitting: {problem_code}")
            print('='*50)
            
            if self.submit_code(problem_code, file_path):
                success += 1
                print(f"✓ Success ({success}/{len(cpp_files)})")
            else:
                failed += 1
                print(f"✗ Failed ({failed}/{len(cpp_files)})")
            
            # Wait between submissions to avoid rate limiting
            if cpp_file != cpp_files[-1]:  # Not the last file
                print("Waiting 5 seconds before next submission...")
                time.sleep(5)
        
        print(f"\n{'='*50}")
        print(f"Batch submission complete!")
        print(f"✓ Success: {success}")
        print(f"✗ Failed: {failed}")
        print('='*50)
        print("\nPress Enter to close the script...")
        input()
    
    def submit_random(self):
        """Submit all files from random folder, using Gemini to identify problems"""
        random_folder = Path(self.config.get('random_folder', '~/Desktop/Codeforces/random')).expanduser()
        
        if not random_folder.exists():
            print(f"✗ Random folder not found: {random_folder}")
            return
        
        cpp_files = list(random_folder.glob('*.cpp'))
        
        if not cpp_files:
            print(f"No .cpp files found in {random_folder}")
            return
        
        print(f"Found {len(cpp_files)} files in random folder")
        print("Using Gemini to identify problems...\n")
        
        self.init_driver()
        
        if not self.check_login():
            return
        
        success = 0
        failed = 0
        skipped = 0
        
        for i, cpp_file in enumerate(cpp_files, 1):
            print(f"\n{'='*50}")
            print(f"[{i}/{len(cpp_files)}] Processing: {cpp_file.name}")
            print('='*50)
            
            # Try to identify problem code
            print("Identifying problem code with Gemini...")
            problem_code = self.identify_problem_with_gemini(cpp_file, cpp_file.stem)
            
            if not problem_code:
                print(f"✗ Could not identify problem code")
                failed += 1
                continue
            
            print(f"✓ Identified as: {problem_code}")
            
            # Confirm with user
            print(f"Submit {cpp_file.name} as {problem_code}? (y/n/s=skip): ", end='', flush=True)
            response = input().strip().lower()
            
            if response == 's':
                print("⊘ Skipped")
                skipped += 1
                continue
            elif response != 'y':
                print("✗ Cancelled")
                failed += 1
                continue
            
            # Submit
            if self.submit_code(problem_code, str(cpp_file)):
                success += 1
                print(f"✓ Success ({success}/{len(cpp_files)})")
            else:
                failed += 1
                print(f"✗ Failed ({failed}/{len(cpp_files)})")
            
            # Wait between submissions
            if i < len(cpp_files):
                print("Waiting 5 seconds before next submission...")
                time.sleep(5)
        
        print(f"\n{'='*50}")
        print(f"Random folder submission complete!")
        print(f"✓ Success: {success}")
        print(f"⊘ Skipped: {skipped}")
        print(f"✗ Failed: {failed}")
        print('='*50)
        print("\nPress Enter to close the script...")
        input()

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python submit.py <problem_code>")
        print("       python submit.py --all")
        print("       python submit.py --random")
        print("\nExamples:")
        print("  python submit.py 2167B")
        print("  python submit.py --all          # Submit all from code_folder")
        print("  python submit.py --random       # Submit all from random_folder with AI identification")
        sys.exit(1)
    
    submitter = CodeforcesSubmitter()
    
    if sys.argv[1] == "--all":
        submitter.submit_all()
    elif sys.argv[1] == "--random":
        submitter.submit_random()
    else:
        submitter.run(sys.argv[1])