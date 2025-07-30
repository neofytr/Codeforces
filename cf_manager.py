#!/usr/bin/env python3
import os
import sys
import subprocess
import json
from datetime import datetime
from pathlib import Path
import argparse
from google import genai

class CFManager:
    def __init__(self):
        self.root_dir = Path.cwd()
        self.config_file = self.root_dir / '.cf_config.json'
        self.load_config()
        
    def load_config(self):
        """Load configuration or create default"""
        default_config = {
            'editor_command': 'code',  # VS Code command
            'cpp_template': '''#include <bits/stdc++.h>
using namespace std;

// Problem: {problem_name}
// URL: {problem_url}
// Difficulty: {difficulty}
// Tags: 
// Strategy: 

int main() {{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Solution here
    
    return 0;
}}''',
            'md_template': '''# {problem_name}

{problem_link}

## Problem Statement
<!-- Describe the problem here -->

## Approach
<!-- Explain your approach -->

## Key Insights
<!-- List key insights and tricks -->

## Complexity
- Time: O()
- Space: O()

## Code
```cpp
{code}
```

## Notes
<!-- Any additional notes -->
'''
        }
        
        if self.config_file.exists():
            with open(self.config_file, 'r') as f:
                self.config = json.load(f)
        else:
            self.config = default_config
            self.save_config()
    
    def save_config(self):
        """Save current configuration"""
        with open(self.config_file, 'w') as f:
            json.dump(self.config, f, indent=2)
    
    def create_topic(self, topic_name):
        """Create a new topic folder structure"""
        topic_path = self.root_dir / topic_name
        
        if topic_path.exists():
            print(f"❌ Topic '{topic_name}' already exists!")
            return False
        
        # Create folder structure
        topic_path.mkdir()
        (topic_path / 'problems').mkdir()
        (topic_path / 'journal').mkdir()
        
        # Create topic management script
        prog_script = topic_path / 'prog'
        self.create_prog_script(prog_script, topic_name)
        
        # Make it executable
        os.chmod(prog_script, 0o755)
        
        # Create global topic summary
        summary_file = topic_path / 'README.md'
        with open(summary_file, 'w') as f:
            f.write(f"""# {topic_name}

## Overview
Collection of problems and solutions for {topic_name}.

## Problems Solved
<!-- This will be auto-updated -->

## Key Techniques
<!-- Common patterns and tricks for this topic -->

## Progress
- Total Problems: 0
- Solved: 0
- Success Rate: 0%

---
*Auto-generated on {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}*
""")
        
        print(f"✅ Created topic '{topic_name}' successfully!")
        print(f"📁 Structure: {topic_name}/{{problems, journal, prog, README.md}}")
        print(f"🚀 Usage: cd {topic_name} && ./prog <problem_name>")
        
        return True
    
    def create_prog_script(self, script_path, topic_name):
        """Create the prog script for managing problems"""
        script_content = f'''#!/usr/bin/env python3
import sys
import os
from pathlib import Path
sys.path.append('{self.root_dir}')
from {Path(__file__).stem} import ProblemManager

if __name__ == "__main__":
    manager = ProblemManager("{topic_name}")
    manager.run()
'''
        
        with open(script_path, 'w') as f:
            f.write(script_content)

class ProblemManager:
    def __init__(self, topic_name):
        self.topic_name = topic_name
        self.topic_path = Path.cwd()
        self.problems_dir = self.topic_path / 'problems'
        self.journal_dir = self.topic_path / 'journal'
        self.summary_file = self.topic_path / 'README.md'
        
        # Load config from parent directory
        config_file = self.topic_path.parent / '.cf_config.json'
        with open(config_file, 'r') as f:
            self.config = json.load(f)
    
    def run(self):
        """Main entry point for problem management"""
        if len(sys.argv) < 2:
            self.show_help()
            return
        
        command = sys.argv[1]
        
        if command == 'help' or command == '-h':
            self.show_help()
        elif command == 'new' and len(sys.argv) >= 3:
            problem_name = sys.argv[2]
            difficulty = sys.argv[3] if len(sys.argv) > 3 else "Unknown"
            problem_url = sys.argv[4] if len(sys.argv) > 4 else None
            self.create_problem(problem_name, difficulty, problem_url)
        elif command == 'done' and len(sys.argv) >= 3:
            problem_name = sys.argv[2]
            self.mark_done(problem_name)
        elif command == 'list':
            self.list_problems()
        elif command == 'stats':
            self.show_stats()
        elif command == 'open' and len(sys.argv) >= 3:
            problem_name = sys.argv[2]
            self.open_problem(problem_name)
        elif command == 'run':
            problem_name = sys.argv[2]
            self.test_problem(problem_name)
        else:
            # Default behavior: create new problem
            problem_name = sys.argv[1]
            difficulty = sys.argv[2] if len(sys.argv) > 2 else "Unknown"
            problem_url = sys.argv[3] if len(sys.argv) > 3 else None
            self.create_problem(problem_name, difficulty, problem_url)
    
    def show_help(self):
        """Display help information"""
        print(f"""
🏆 Codeforces Problem Manager - {self.topic_name}

Usage:
  ./prog <problem_name> [difficulty] [problem_url]  Create new problem
  ./prog new <problem_name> [diff] [url]            Create new problem  
  ./prog done <problem_name>                        Mark problem as solved
  ./prog open <problem_name>                        Open existing problem
  ./prog list                                       List all problems
  ./prog stats                                      Show statistics
  ./prog help                                       Show this help

Examples:
  ./prog 1676C medium https://codeforces.com/problem/1676/C
  ./prog sliding_window easy https://leetcode.com/problems/sliding-window-maximum/
  ./prog done 1676C
  ./prog list
""")
    
    def test_problem(self, problem_name):
        problem_dir = self.problems_dir / problem_name
        if not problem_dir.exists():
            print(f"Problem '{problem_name}' doesn't exist!")
            return

        source_file = problem_dir / f"{problem_name}.cpp"
        if not source_file.exists():
            print(f"No 'main.cpp' found in {problem_dir}")
            return

        input_file = self.topic_path / "test"
        if not input_file.exists():
            print(f"Input file '{input_file}' doesn't exist!")
            return

        binary_file = problem_dir / "main"

        print("Compiling...")
        compile_cmd = ["g++", "-std=c++17", "-O2", str(source_file), "-o", str(binary_file)]
        try:
            subprocess.run(compile_cmd, check=True)
        except subprocess.CalledProcessError:
            print("Compilation failed!")
            return

        print("Running...")
        try:
            result = subprocess.run(
            [str(binary_file)],
            stdin=open(input_file),
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
            )
            print(f"Output:\n{result.stdout}", end="")  # Properly formatted output
            if result.stderr:
                print("Errors:\n", result.stderr)
        except Exception as e:
            print("Execution failed:", e)

        
    def create_problem(self, problem_name, difficulty="Unknown", problem_url=None):
        """Create a new problem"""
        problem_dir = self.problems_dir / problem_name
        
        if problem_dir.exists():
            print(f"❌ Problem '{problem_name}' already exists!")
            self.open_problem(problem_name)
            return
        
        problem_dir.mkdir()
        
        # Create C++ file
        cpp_file = problem_dir / f"{problem_name}.cpp"
        cpp_content = self.config['cpp_template'].format(
            problem_name=problem_name,
            difficulty=difficulty,
            problem_url=problem_url or "Not provided"
        )
        with open(cpp_file, 'w') as f:
            f.write(cpp_content)
        
        # Create markdown file
        md_file = problem_dir / f"{problem_name}.md"
        
        # Format problem link for markdown
        if problem_url:
            if 'codeforces.com' in problem_url:
                problem_link = f"🔗 **Problem Link:** [Codeforces Problem]({problem_url})"
            elif 'leetcode.com' in problem_url:
                problem_link = f"🔗 **Problem Link:** [LeetCode Problem]({problem_url})"
            elif 'atcoder.jp' in problem_url:
                problem_link = f"🔗 **Problem Link:** [AtCoder Problem]({problem_url})"
            elif 'codechef.com' in problem_url:
                problem_link = f"🔗 **Problem Link:** [CodeChef Problem]({problem_url})"
            else:
                problem_link = f"🔗 **Problem Link:** [Problem Link]({problem_url})"
        else:
            problem_link = "🔗 **Problem Link:** Not provided"
        
        md_content = self.config['md_template'].format(
            problem_name=problem_name,
            problem_link=problem_link,
            code="// Code will be auto-generated when marked as done"
        )
        with open(md_file, 'w') as f:
            f.write(md_content)
        
        # Create problem metadata
        meta_file = problem_dir / 'meta.json'
        metadata = {
            'name': problem_name,
            'difficulty': difficulty,
            'url': problem_url,
            'created': datetime.now().isoformat(),
            'status': 'unsolved',
            'attempts': 0,
            'solved_at': None
        }
        with open(meta_file, 'w') as f:
            json.dump(metadata, f, indent=2)
        
        url_info = f" (URL: {problem_url})" if problem_url else ""
        print(f"✅ Created problem '{problem_name}' (Difficulty: {difficulty}){url_info}")
        
        # Open in VS Code
        self.open_problem(problem_name)
    
    def open_problem(self, problem_name):
        """Open problem files in VS Code"""
        problem_dir = self.problems_dir / problem_name
        
        if not problem_dir.exists():
            print(f"❌ Problem '{problem_name}' not found!")
            return
        
        cpp_file = problem_dir / f"{problem_name}.cpp"
        md_file = problem_dir / f"{problem_name}.md"
        
        # Open both files
        try:
            subprocess.run([self.config['editor_command'], str(cpp_file), str(md_file)])
            print(f"🚀 Opened {problem_name} in VS Code")
        except Exception as e:
            print(f"❌ Failed to open VS Code: {e}")
    
    def mark_done(self, problem_name):
        problem_dir = self.problems_dir / problem_name
        
        if not problem_dir.exists():
            print(f"❌ Problem '{problem_name}' not found!")
            return
        
        cpp_file = problem_dir / f"{problem_name}.cpp"
        md_file = problem_dir / f"{problem_name}.md"
        meta_file = problem_dir / 'meta.json'
        
        with open(meta_file, 'r') as f:
            metadata = json.load(f)
        
        metadata['status'] = 'solved'
        metadata['solved_at'] = datetime.now().isoformat()
        metadata['attempts'] += 1
        
        with open(meta_file, 'w') as f:
            json.dump(metadata, f, indent=2)
        
        self.generate_ai_docs(cpp_file, md_file, problem_name)
        
        self.update_global_summary()
        
        print(f"🎉 Marked '{problem_name}' as solved!")
        print(f"📝 Generated AI documentation")
        
        print("Pushing to github...")
        gitCommitMsg = f"Done with {problem_name}"
        command = f"cd .. && git add . && git commit -m '{gitCommitMsg}' && git push -u origin main"
        result = subprocess.run(command, shell=True, capture_output=True)
        print(result.stdout)
        print("Done!")
        
    
    def generate_ai_docs(self, cpp_file, md_file, problem_name):
        """Generate documentation using Gemini AI"""
        try:
            # Read the C++ code
            with open(cpp_file, 'r') as f:
                cpp_code = f.read()
            
            # Initialize Gemini
            api_key = os.getenv('GEMINI_API_KEY')
            if not api_key:
                print("⚠️ GEMINI_API_KEY not found. Skipping AI documentation.")
                return
            
            client = genai.Client(api_key=api_key)
            
            # Create prompt for Gemini
            prompt = f"""
Analyze this competitive programming solution and generate comprehensive documentation:

```cpp
{cpp_code}
```

Please provide:
1. Problem description (infer from code and comments, including any URL mentioned)
2. Approach explanation
3. Key insights and algorithmic techniques used
4. Time and space complexity analysis
5. Important code patterns or tricks used
6. Any edge cases handled

Format the response as a clean markdown document suitable for documentation.
Focus on the algorithmic insights and learning points.
If there's a problem URL in the comments, make sure to reference it appropriately.
"""
            
            response = client.models.generate_content(
                model="gemini-2.0-flash-exp",
                contents=prompt
            )
            
            # Update the markdown file
            with open(md_file, 'w') as f:
                f.write(f"# {problem_name}\n\n")
                f.write(response.text)
                f.write(f"\n\n## Original Code\n```cpp\n{cpp_code}\n```\n")
                f.write(f"\n---\n*Documentation generated on {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}*\n")
            
            print("🤖 AI documentation generated successfully!")
            
        except Exception as e:
            print(f"❌ Failed to generate AI docs: {e}")
    
    def update_global_summary(self):
        """Update the global topic summary"""
        problems = list(self.problems_dir.glob('*/meta.json'))
        total_problems = len(problems)
        solved_problems = 0
        
        problem_list = []
        key_techniques = set()
        
        for meta_path in problems:
            with open(meta_path, 'r') as f:
                meta = json.load(f)
            
            if meta['status'] == 'solved':
                solved_problems += 1
                status_icon = "✅"
            else:
                status_icon = "⏳"
            
            problem_list.append(f"- {status_icon} **{meta['name']}** ({meta['difficulty']}) - {meta['status']}")
            
            # Extract techniques from code (basic keyword matching)
            cpp_file = meta_path.parent / f"{meta['name']}.cpp"
            if cpp_file.exists():
                with open(cpp_file, 'r') as f:
                    code = f.read().lower()
                    
                # Simple technique detection
                if 'sort' in code: key_techniques.add('Sorting')
                if 'binary_search' in code or 'lower_bound' in code: key_techniques.add('Binary Search')
                if 'dp' in code or 'memo' in code: key_techniques.add('Dynamic Programming')
                if 'graph' in code or 'dfs' in code or 'bfs' in code: key_techniques.add('Graph Algorithms')
                if 'two' in code and 'pointer' in code: key_techniques.add('Two Pointers')
        
        success_rate = (solved_problems / total_problems * 100) if total_problems > 0 else 0
        
        # Update README
        content = f"""# {self.topic_name}

## Overview
Collection of problems and solutions for {self.topic_name}.

## Problems Solved
{chr(10).join(problem_list) if problem_list else '- No problems yet'}

## Key Techniques
{chr(10).join(f'- {tech}' for tech in sorted(key_techniques)) if key_techniques else '- Techniques will be detected automatically'}

## Progress
- Total Problems: {total_problems}
- Solved: {solved_problems}
- Success Rate: {success_rate:.1f}%

---
*Last updated on {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}*
"""
        
        with open(self.summary_file, 'w') as f:
            f.write(content)
    
    def list_problems(self):
        """List all problems with their status"""
        problems = list(self.problems_dir.glob('*/meta.json'))
        
        if not problems:
            print("📝 No problems found in this topic.")
            return
        
        print(f"\n📊 Problems in {self.topic_name}:\n")
        
        for meta_path in sorted(problems):
            with open(meta_path, 'r') as f:
                meta = json.load(f)
            
            status_icon = "✅" if meta['status'] == 'solved' else "⏳"
            created = datetime.fromisoformat(meta['created']).strftime('%Y-%m-%d')
            
            # Show URL if available
            if meta.get('url'):
                url_display = f" - {meta['url']}"
            else:
                url_display = ""
            
            print(f"{status_icon} {meta['name']} ({meta['difficulty']}) - Created: {created}{url_display}")
        
        print()
    
    def show_stats(self):
        """Show detailed statistics"""
        problems = list(self.problems_dir.glob('*/meta.json'))
        
        if not problems:
            print("📊 No statistics available yet.")
            return
        
        total = len(problems)
        solved = sum(1 for p in problems if json.load(open(p))['status'] == 'solved')
        unsolved = total - solved
        
        print(f"""
📊 Statistics for {self.topic_name}:

Total Problems: {total}
✅ Solved: {solved}
⏳ Unsolved: {unsolved}
📈 Success Rate: {solved/total*100:.1f}%

Recent Activity:
""")
        
        # Show recent problems
        recent = sorted(problems, key=lambda p: json.load(open(p))['created'], reverse=True)[:5]
        for meta_path in recent:
            with open(meta_path, 'r') as f:
                meta = json.load(f)
            created = datetime.fromisoformat(meta['created']).strftime('%m-%d %H:%M')
            status_icon = "✅" if meta['status'] == 'solved' else "⏳"
            print(f"  {status_icon} {meta['name']} - {created}")

def main():
    """Main CLI interface"""
    parser = argparse.ArgumentParser(description='Codeforces Practice Manager')
    parser.add_argument('command', nargs='?', default='help', 
                       help='Command to execute (create-topic, help)')
    parser.add_argument('topic_name', nargs='?', 
                       help='Topic name for create-topic command')
    
    args = parser.parse_args()
    
    if args.command == 'create-topic':
        if not args.topic_name:
            print("❌ Please provide a topic name: python cf_manager.py create-topic <topic_name>")
            return
        
        manager = CFManager()
        manager.create_topic(args.topic_name)
    
    elif args.command == 'help' or args.command is None:
        print("""
🏆 Codeforces Practice Manager

Usage:
  python cf_manager.py create-topic <topic_name>         Create new topic structure
  python cf_manager.py help                              Show this help

After creating a topic:
  cd <topic_name>
  ./prog <problem_name> [difficulty] [url]               Create and open new problem
  ./prog done <problem_name>                             Mark as solved (generates AI docs)
  ./prog list                                            List all problems
  ./prog stats                                           Show statistics

Examples:
  ./prog 1676C medium https://codeforces.com/problem/1676/C
  ./prog sliding_window easy https://leetcode.com/problems/sliding-window-maximum/
  ./prog done 1676C

Features:
🤖 AI-powered solution documentation using Gemini
📁 Organized folder structure per topic  
🔗 Problem URL tracking and linking
📊 Progress tracking and statistics
🚀 VS Code integration
📝 Automatic markdown generation
🎯 Metadata tracking for each problem

Setup:
1. Set GEMINI_API_KEY environment variable
2. Ensure 'code' command is available (VS Code CLI)
3. Run from your root Codeforces directory
""")
    
    else:
        print(f"❌ Unknown command: {args.command}")
        print("Use 'python cf_manager.py help' for usage information")

if __name__ == "__main__":
    main()