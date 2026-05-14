TEMPLATE = subdirs
SUBDIRS += \
    NetworkLibrary \
    PIconMaker \
    updater

CONFIG += ordered

OTHER_FILES += $$PWD/.qmake.conf
