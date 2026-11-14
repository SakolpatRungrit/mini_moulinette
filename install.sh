#!/usr/bin/env bash
# Adds a `mini` alias to your shell config so you can run mini-moulinette anywhere.

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"
LINE="alias mini='$DIR/mini'"
chmod +x "$DIR/mini"

added=""
for rc in "$HOME/.zshrc" "$HOME/.bashrc"; do
	shell_name="$(basename "$rc" | sed 's/^\.//; s/rc$//')"
	# configure the rc file if it exists or belongs to the current shell
	if [ -f "$rc" ] || [ "$(basename "${SHELL:-}")" = "$shell_name" ]; then
		touch "$rc"
		{ grep -v "^alias mini=" "$rc" || true; } > "$rc.mini-tmp"
		mv "$rc.mini-tmp" "$rc"
		printf '%s\n' "$LINE" >> "$rc"
		added="$added $rc"
	fi
done

if [ -z "$added" ]; then
	echo "Couldn't find ~/.zshrc or ~/.bashrc. Add this line to your shell config yourself:"
	echo "  $LINE"
	exit 1
fi
echo "Added the 'mini' alias to:$added"
echo
echo "Open a new terminal (or run: source ~/.zshrc), then:"
echo "  cd ~/your-piscine/C04 && mini"
