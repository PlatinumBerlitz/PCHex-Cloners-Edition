#What is this?
PCHex++ is a 3ds homebrew POKEMON XY and ORAS save file editor with a touch based gui.

#How do i get it?
You can compile it from source or check [its topic on GBATemp:](https://gbatemp.net/threads/wip-pchex-pchex-with-its-own-gui.405302/ for precompiled binaries, it also contains more detalied information)

#How can i use it?
You can launch the 3dsx binary from the 3ds Homebrew Launcher or install the cia binary with your favourite tool

#How can i compile it?
To compile this project you will need a working devkitPRO enviroment with ctrulib, sf2dlib, sftdlib, sfil and hbkb.
You can make a cia-compatible elf, a 3dsx binary or a 3dsx DEBUG binary to be used on citra, you can produce the desired binary de-commenting [these lines](https://github.com/Slashcash/PCHex-plusplus/blob/new-release/include/core/compileoptions.h#L4#L6).
On Windows you can convert your cia-compatible elf into a pleasant cia with the command make cia.
