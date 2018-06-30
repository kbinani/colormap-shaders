#!/bin/bash

(
	cd "$(dirname "$0")/.."

	bash tool/transcode.sh
	bash tool/create_c++_header.sh

	COMMIT_ID=$(git rev-parse HEAD)

	BRANCH_NAME=$(date "+%s")
	git checkout --orphan $BRANCH_NAME
	ls -a1 | grep -v include | grep -v shaders | grep -v '^.$' | grep -v '^..$' | grep -v '^.git$'| xargs git rm -rf
	git add -A include shaders
	git commit -m "Generated: $COMMIT_ID"

	git checkout master
	if git merge --allow-unrelated-histories $BRANCH_NAME -m "Generated: $COMMIT_ID"; then
		git reset --hard HEAD^
		git checkout $COMMIT_ID
	else
		git checkout --theirs .
		git add -A .
		git commit -m "Generated: $COMMIT_ID"
	fi
)
