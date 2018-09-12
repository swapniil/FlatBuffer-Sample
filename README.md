# FlatBuffer-Sample

This is a demo application to use Google's Flatbuffer in C++.
Its for learning purposes and no copyright has been applied on the repo.

Prerequisite:

    Flatbuffer is already installed on system
        Refer: http://google.github.io/flatbuffers/flatbuffers_guide_building.html
        After installation check if flatcompiler has been available in system in bin dir
                `which flatc`
            If this command fails copy 'flatc' binaray available in flatbuffers source after successful build
            The destination path must be avalible in enviornment so that shell can find and execute binary
                as a well known path copy flatc to '/usr/bin/'
        Check for the Headers of Flatbuffers:
             `ls -ltr /usr/local/include/flatbuffers/`

Build steps:
    make

Clean Steps:
    make clean


    
