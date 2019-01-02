#! bin/sh

tr "\n" " " < Parts.html | sed -r "s/ <td data-sort-value=\"[0-9]*\"> <div class=\"center\"><div class=\"floatnone\"><a href=\"https:\/\/wiki.kerbalspaceprogram.com\/wiki\/File:[^\"]*\" class=\"image\"><img alt=\"[^\"]*\" src=\".\/Parts_files\/([^\"]*)\"([^ ]* ){10}[^>]*>([^<]*)<\/a>/\n@@@\1 \3\n/g" | grep -o "^@@@.*" | sed -r "s/@@@([^ ]*) (.*)/\1 \2.png/g" | sed -r "s/( [^ ]*) /\1\\ /g"
