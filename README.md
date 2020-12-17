# Notes app
This is a very basic QT based note taking application. It is very much a pre-alpha for now.

## Features
The feature set (current and planned) are:
  - Rich text editing (ongoing).
  - Folder support to organize notes (future).
  - Light/dark theme from settings (future).
  - Tag support (future).
  - Online sync support (future).
  - Vault support (future).
  - Keyword search support (future).
  - Package up as a snap application for Linux and dmg for Mac (future).

## Building
This project needs QT 5 development files and SQLITE development files to build. These are availeble from repos in Ubuntu. For building on Mac OS, you can install QT via the official installer and sqlite from homebrew.

Once you have those, do the following
```
git clone https://github.com/amartya00/notes.git
cd notes
mkdir _build
cd _buils
meson ..
ninja
```

To run, you can execute the generated binary
```
src/notes
```
