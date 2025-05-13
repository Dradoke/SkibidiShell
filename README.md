# 🐚 SkibidiShell

## Description

**Minishell** is a project aimed at recreating a minimalist UNIX shell.  
It’s a low-level exercise designed to handle processes, memory management, signals, parsing, redirections, and more.

This project is done as a team as part of our curriculum at 42 school.

---

## ✅ Team Development Best Practices

> As this is a group project, we follow strict guidelines to ensure smooth collaboration and clean, maintainable code.

---

### 🧱 Project Structure

- Follow the repository structure defined at the beginning of the project.
- Do not add new folders or files without team approval.
- Do not merge code that doesn't compile or is broken.

---

### 🔁 Git & GitHub

#### Branches

- The `main` and `dev` branches are protected (no direct push).
- Each new feature or fix must be developed in a dedicated branch:
```bash
	git checkout -b feat/parser
	git checkout -b fix/leaks
```
---

###  📆 Daily Routine (Rebase & Sync)

To avoid conflicts, stay in sync with others, and ensure smooth integration, rebasing is mandatory every day.

#### 🔄 Start of the Day

Before starting work:
```bash
	git fetch origin
	git rebase origin/main
```
#### 🛑 End of the Day

Before pushing or opening a PR:
```bash
	git pull --rebase origin main
```
##### ➡️ Goal: Keep a clean, linear history and avoid unnecessary conflicts.
##### ⚠️ Avoid uncontrolled git push -f, especially if others have worked on the branch.

---

### ✅ Pull Requests

- One PR = one clear task (no mixing topics).

- Write a clear and precise description.

- No merge without at least 1 review from another team member.

- Delete the branch after merging.

---

### ✍️ Commit Conventions

Use clear and concise commit messages:
```bash
	git commit -m "feat: add support for cd command"
	git commit -m "fix: fix memory leak in exec"
```
#### Recommended Prefixes:

- feat: new feature

- fix: bug fix

- refactor: code improvement with no behavior change

- test: adding or modifying tests

- docs: documentation

---

### 🧹 Code Hygiene

- Code must be clean, indented, and free of debug artifacts (printf, unused comments...).

- No dead code or unused functions.

- Follow the school's coding standard (Norminette if you're at 42).

---

### 🛠 Useful Tools

- valgrind for detecting memory leaks.

- make re to compile cleanly before each push.

- test.sh or a tests/ directory to validate shell behavior.

---

### 🤝 Team Communication

- Stay connected through the team’s chosen platform (Discord, Slack, etc.).

- Notify when a feature is being worked on or completed.

- Don’t hesitate to ask for help when blocked.

---

### 🧨 Absolutely Avoid

- Working directly on main.

- Merging a PR without review.

- Pushing broken or incomplete code.

- Commits like wip, test, or debug.

---

### 🚀 Good luck team!

- This README is here to save time, prevent conflicts, and help deliver a clean project.
- Let’s work smart, communicate well, and enjoy the process 💪