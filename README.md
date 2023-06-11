# bdayer

UNIX birthday tracker. No dependencies, just a ~100 lines of pure C99.

```
162 day(s)      Name Surname
10 day(s)       Me
32 day(s)       Some day in the future
0 day(s)        Billy
-89 day(s)      Albert Einstein
-102 day(s)     Frédéric Chopin
```

Negative numbers indicate those who have already had a birthday this year.

# INSTALL

```bash
git clone https://github.com/kovmir/bdayer.git
cd bdayer
make
sudo make install
```

# USAGE

Create a text file with each line of the following format:

```
# <day>,<month>,<anything>
# Like that...
11,21,Name Surname
06,22,Me
07,14,Some day in the future

03,14,Albert Einstein
03,01,Frédéric Chopin

# Comments are allowed, empty lines are skipped.
# I am going to call this file a roster.
```

Then invoke `bdayer` like that:

```bash
export BDAYER_ROSTER=/path/to/roster # Put it in your shell's rc file.
bdayer
```

Put your roster in Git, then use its power to sync it across machines and
commit changes.

# FAQ

**Q: How do I sort birthdays depending on how soon they are?**

A: `bdayer | sort -n` or `bdayer | sort -rn` to reverse the order.

**Q: How do I exclude those who have already had a birthday this year?**

A: `bdayer | grep -v ^-`

**Q: How to sort and exclude those whose birthdays have already been?**

A: `bdayer | grep -v ^- | sort -n`

**Q: How do I see who has a birthday today?**

A: `bdayer | grep ^0`.

**Q: How do I fit all of my birthdays into the screen?**

A: `bdayer | less`.

**Q: How do I see 2 most soonish birthdays?**

A: `bdayer | grep -v ^- | sort -n | head -n2`

**Q: How do I avoid typing long commands?**

```bash
alias bsn='bdayer | grep -v ^- | sort -n | head -n2' # In your shell's rc file.
bsn # And then it is just the three characters.
```

**Q: How do I ...?**

A: I think you got the point.

**Q: Right, but how do I ...?**

A: The source code is available.
