# mini-moulinette 2

A rebuilt version of [mini-moulinette](https://github.com/k11q/mini-moulinette). It tests your 42 Piscine C exercises (C00 to C08) before you push them.

```
 mini-moulinette  C04  ~/piscine/C04

   OK  ex00  ft_strlen.c            10/10 cases
   OK  ex01  ft_putstr.c            11/11 cases
   KO  ex02  ft_putnbr.c            17/18 cases
    x ft_putnbr(-2147483648)
        output:
          expected: "-2147483648"
          got:      "-("
   OK  ex03  ft_atoi.c              36/36 cases
   ...
  ────────────────────────────────────────
  Passed   5/6 exercises   (KO: ex02)
  Grade    33/100  moulinette stops counting at the first KO (ex02)
```

## Install

```bash
git clone <this repo> ~/mini-moulinette
bash ~/mini-moulinette/install.sh      # adds the `mini` alias to ~/.zshrc / ~/.bashrc
```

Then open a new terminal.

## Use

```bash
cd ~/piscine/C04
mini                 # test every exercise of the day
mini ex03            # just one exercise (also: mini 3, or mini ex03 ex05)
cd ex03 && mini      # inside an exercise folder, it tests just that one
mini C04             # name the day if your folder isn't called C04
mini -v              # also list the cases that passed
mini --help          # every option
```

| Option | What it does |
| --- | --- |
| `-v`, `--verbose` | show passing cases and every failure (normally at most 3 per exercise are shown) |
| `-n`, `--no-norm` | skip norminette |
| `-a`, `--no-asan` | don't use AddressSanitizer (faster, misses memory bugs) |
| `-t SEC` | time limit per test case (default 3 s) |
| `-d PATH` | test another folder |
| `-l`, `--list` | list the days and exercises that have tests |
| `-u`, `--update` | `git pull` the latest tests |

## Reading the results

- `x` (red): a required case failed. The exercise is **KO**.
- `!` (yellow): an extra edge case failed. This is only a **warning**. These cover things the subject leaves undefined or doesn't spell out, such as bytes above 127, `ft_swap(&a, &a)`, `ft_is_prime(INT_MAX)` speed, or macros without parentheses. The real moulinette may or may not test them.
- **Grade** follows the Piscine rule: counting stops at the first KO, and a norm error gives 0 for the whole day.

## What each exercise goes through

1. **Files**: the expected file is in `exNN/`, with a hint if the name is slightly off. You're warned about extra files you shouldn't push.
2. **norminette**, if it's installed.
3. **Compile with `cc -Wall -Wextra -Werror`**, exactly like the moulinette.
4. **Prototype**: your function must match the subject's prototype, otherwise you get a "your prototype doesn't match" message.
5. **No `main()`** left in a function exercise.
6. **Forbidden functions**: checked with `nm`, so `printf`, `strlen`, and even `isspace()` macros are caught.
7. **Tests**: every case runs in its own process with a time limit. A segfault or an infinite loop fails only that case and tells you which one. With AddressSanitizer, memory bugs that don't crash are caught too (for example `malloc(len)` instead of `malloc(len + 1)`), with the file and line:
   ```
   x ft_strdup("Hello")
       memory error: heap-buffer-overflow (WRITE of size 1) at ft_strdup.c:12 (ft_strdup)
   ```

Your folder is never touched: everything is built in a temp folder and deleted afterwards. The original copied a `mini-moul/` folder into your repo, which you could push by accident.

## Changes from the original

| | original | mini-moulinette 2 |
| --- | --- | --- |
| Coverage | some exercises compile-only (C02 ex12, C08) | real tests for all 68 exercises of C00 to C08, about 900 cases |
| A crash | kills the whole exercise's tests | fails one case and names it (segfault, timeout, memory error) |
| Infinite loop | hangs forever | times out after 3 s |
| Memory bugs | not detected | AddressSanitizer, with file:line |
| Forbidden functions | not checked | checked |
| Prototype, `main()` left in | confusing compile errors | clear messages |
| Run one exercise | no | `mini ex03` |
| Writes into your repo | yes (`mini-moul/`) | no |
| Norminette | never actually ran (the function was defined after it was called) | counts as KO, as on the real thing |

## Adding or changing a test

Each exercise is one file, `tests/CXX/exYY/test.c`, whose first lines describe it:

```c
// mm:files   ft_atoi.c
// mm:allowed
// mm:proto   int ft_atoi(char *str);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	CASE("ft_atoi(\"  -42\")")
		CHECK_INT("return value", ft_atoi("  -42"), -42);
	SOFT("an edge case that only warns")
		CHECK_INT("return value", ft_atoi("--1"), 1);
	return (mm_done());
}
```

The checks are `CHECK_INT`, `CHECK_STR`, `CHECK_MEM`, `CHECK_PTR`, `CHECK_SIGN`, `CHECK_OUTPUT` (what was written to stdout), `CHECK(cond, msg...)` and, for programs, `RUN(...)` + `CHECK_PROG_OUTPUT`. See `framework/mm.h`. Other `// mm:type` values are `prog` (C06) and `header` (C08).

## Limits

- Tests cover C00 to C08. C09 to C13 aren't done yet.
- It isn't the real moulinette. Passing here is a strong sign, not a guarantee.
- AddressSanitizer needs a compiler that supports it. If `cc` doesn't, `gcc` is used automatically for the test build, while your code is still checked with `cc`. If neither has it, you'll see a notice.

## Credits

Based on [mini-moulinette](https://github.com/k11q/mini-moulinette) by Khairul Haaziq (MIT).
