#!/bin/bash
sudo dnf install -y kdiff3
git config --global --add merge.tool kdiff3
git config --global --add mergetool.kdiff3.path "/bin/kdiff3"
git config --global --add mergetool.kdiff3.trustExitCode false

git config --global --add diff.guitool kdiff3
git config --global --add difftool.kdiff3.path "/bin/kdiff3"
git config --global --add difftool.kdiff3.trustExitCode false
