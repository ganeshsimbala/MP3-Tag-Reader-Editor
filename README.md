🎵 MP3 Tag Reader & Editor
==========================

📌 Overview
-----------
The MP3 Tag Reader and Editor is a command-line utility written in C for reading and modifying ID3 tags (metadata) in MP3 files. ID3 tags store information like song title, artist, album, year, genre, and more—helping media players organize and display music details.

This tool allows users to inspect and modify ID3v1 and/or ID3v2 tags embedded within .mp3 files.

🎯 Objectives
-------------
- Read metadata from MP3 files (ID3v1 and optionally ID3v2)
- Edit and update specific fields like title, artist, and album
- Provide a simple command-line interface for automation and scripting
- Understand the binary structure of MP3 and tag formats
- Build a practical application demonstrating file parsing and byte-level manipulation in C

✨ Features
----------
- View ID3v1 tag metadata
- Edit and update specific tag fields
- Validate file type and tag presence
- Detect if ID3 tag is missing or malformed
- CLI-based for fast operation
- Safe tag rewriting without corrupting audio data
- (Optional) ID3v2 support for extended metadata

🧠 What are ID3 Tags?
---------------------
ID3v1 tags are 128-byte metadata blocks located at the end of MP3 files and contain the following fields:

Field     | Bytes | Description
----------|--------|-------------
Title     | 30     | Song title
Artist    | 30     | Artist or band name
Album     | 30     | Album title
Year      | 4      | Release year
Comment   | 28/30  | Comment or note
Genre     | 1      | Encoded genre number

Tags start with "TAG" followed by the fields above.

🧱 Project Structure
--------------------
mp3_tag_editor/
├── include/
│   └── tag.h              # Function declarations
├── src/
│   ├── reader.c           # Read tag logic
│   ├── writer.c           # Modify tag logic
│   ├── utils.c            # File and string utilities
│   └── main.c             # CLI entry point
├── assets/
│   └── sample.mp3         # Test MP3 files
├── Makefile               # Compilation instructions
├── README.md              # Documentation
└── output/
    └── updated.mp3        # Modified file with new tags

⚙️ How It Works
---------------
🔍 Reading Tags:
- Open MP3 file in binary mode
- Seek to last 128 bytes of the file
- Parse metadata starting from the "TAG" header
- Extract and display each field

✏️ Editing Tags:
- Create or update the 128-byte tag structure
- Seek to the end of the file (or overwrite existing tag)
- Write the new tag block safely without affecting audio

🚀 Getting Started
------------------
✅ Prerequisites:
- GCC compiler (for C)
- Make (optional)

🔧 Build Instructions:
$ git clone https://github.com/ganeshsimbala/MP3-Tag-Reader-Editor.git
$ cd mp3-tag-editor
$ make

Or compile manually:
$ gcc -o mp3editor main.c src/*.c

🛠️ Usage
---------
To read MP3 tag:
$ ./mp3editor read song.mp3

To edit MP3 tag:
$ ./mp3editor edit song.mp3 --title "New Title"

Supported options:
--artist "Artist Name"
--album "Album Title"
--year "2024"
--comment "Optional notes"
--genre "17"

🔒 Data Safety
--------------
- Creates a backup copy (optional flag --backup)
- No changes made if file type is invalid or read-only
- Editing is done in-place without corrupting audio

🔬 Sample Output
----------------
Title  : Imagine
Artist : John Lennon
Album  : Greatest Hits
Year   : 1971
Genre  : Rock (17)

📚 Learning Topics
------------------
- Binary file I/O in C
- Byte-level parsing and manipulation
- Structure padding and memory layout
- MP3 and ID3 tag format specifications
- Command-line argument parsing

📄 License
----------
This project is licensed under the MIT License.

👨‍💻 Author
-----------
- Ganesh Simbala — https://github.com/ganeshsimbala

🔗 References
-------------
- https://id3.org/ID3v1
- https://www.geeksforgeeks.org/read-write-id3-tags-mp3-c/
- https://en.wikipedia.org/wiki/ID3

💡 Future Work
--------------
- Support for ID3v2
- GUI interface
- Genre name lookup
- Explorer integration
