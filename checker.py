import subprocess
import sys

test_cases = ["my_var3$USER$USER$USER=$USER", "my_var4=$USERafds", "HOME=aaUSER:22USER:f", "HOME=aa$USER:22$USER:f",
              "my_var3=aa$USER:22$USER:f", "my_var4=$USER",
              "my_var3=aa$USER:22$USE:hjhjh", "my_var3aa$USER:22USE:f ",
              "2my_var3=aa$USER:22$USE:hjhjh$USERdhajdhaj$USER", "my_var3**=aa$USER:22$USE:hjhjh$USERdhajdhaj$USER",
              "my_var3**=aa$USER:22$USE:hjhjh$USERdhajdhaj$USER"]

compile_process = subprocess.run("make re", shell=True, text=True, capture_output=True)

if compile_process.returncode != 0:
    print("Compilation failed!")
    print(compile_process.stderr)
    sys.exit(1)

for i in range(len(test_cases)):
    minishell_run = subprocess.run(f"./minishell {test_cases[i]}", shell=True, text=True, capture_output=True)
    minishell_output = minishell_run.stdout.strip()

    cmd = f"export {test_cases[i]} && env"
    all_env_vars = subprocess.run(cmd, shell=True, text=True, capture_output=True)

    if (minishell_output in all_env_vars.stdout.strip()):
        print(f"✅ Test {test_cases[i]} passed! ✅")
    else:
        print(f"❌ Test {test_cases[i]} failed! ❌")

    valgrind_process = subprocess.run(f"valgrind ./minishell {test_cases[i]}", shell=True, text=True,
                                      capture_output=True)

    if ("All heap blocks were freed -- no leaks are possible" in valgrind_process.stderr):
        print("✅ No memory leaks ✅")
    else:
        print(f"❌ Memory leaks found! ❌")
    print("######################################")
