import os

def normalize_file(filepath):
    """ Reads a file and strips all whitespace/tabs. """
    try:
        with open(filepath, 'r') as f:
            lines = f.readlines()
            return [line.replace(" ", "").replace("\t", "").strip() for line in lines if line.strip() != '']
    except FileNotFoundError:
        return None

def grade_problem(filename, orig_name, sol_name):
    print(f"\n{'='*40}")
    print(f"GRADING: {filename}")
    print(f"{'='*40}")
    
    # Paths relative to the root of the repository
    stud_path = filename
    orig_path = os.path.join('.hidden', orig_name)
    sol_path = os.path.join('.hidden', sol_name)

    stud_code = normalize_file(stud_path)
    orig_code = normalize_file(orig_path)
    sol_code = normalize_file(sol_path)

    if stud_code is None:
        print(f"❌ Error: Could not find your submitted {filename}.")
        return 0

    expected_deletions = [line for line in orig_code if line not in sol_code]
    expected_additions = [line for line in sol_code if line not in orig_code]

    student_deletions = [line for line in orig_code if line not in stud_code]
    student_additions = [line for line in stud_code if line not in orig_code]

    fixes = 0
    penalties = 0

    # Calculate +2 Points for Bug Fixes
    for added in list(student_additions):
        if added in expected_additions:
            fixes += 1
            student_additions.remove(added) 
            expected_additions.remove(added) 

    # Calculate -1 Penalty for unnecessary changes
    penalties += len(student_additions)
    for deleted in student_deletions:
        if deleted not in expected_deletions:
            penalties += 1

    total_score = max(0, (fixes * 2) - (penalties * 1))

    print(f"✅ Correct Bug Fixes:   {fixes} (+{fixes * 2} points)")
    print(f"❌ Unnecessary Changes: {penalties} (-{penalties} points)")
    print(f"🏆 FINAL SCORE FOR {filename}: {total_score}")
    
    return total_score

def main():
    q1_score = grade_problem("Q1.c", "original_Q1.c", "solution_Q1.c")
    q2_score = grade_problem("Q2.cpp", "original_Q2.cpp", "solution_Q2.cpp")
    
    print(f"\n{'*'*40}")
    print(f"🚀 TOTAL COMPETITION SCORE: {q1_score + q2_score}")
    print(f"{'*'*40}\n")

if __name__ == '__main__':
    main()
