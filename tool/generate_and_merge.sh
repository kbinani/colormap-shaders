#!/bin/bash

function exec {
	echo -e "\033[2m$@\033[0m"
	$@
}

(
	cd "$(dirname "$0")/.."

	exec pwd
	exec git submodule update --init --recursive
	exec rm -rf shaders include/colormap/private samples

	exec bash tool/transcode.sh
	exec bash tool/create_c++_header.sh
	exec bash tool/create_samples.sh

	COMMIT_ID=$(git rev-parse HEAD)

	BRANCH_NAME=$(date "+%s")
	exec git checkout --orphan $BRANCH_NAME

	exec git submodule deinit tool/create_samples/ext/pngpp
	exec git rm -rf tool/create_samples/ext/pngpp

	echo ls -a1 | grep -v include | grep -v shaders | grep -v sample | grep -v '^.$' | grep -v '^..$' | grep -v '^.git$'| xargs git rm -rf
	ls -a1 | grep -v include | grep -v shaders | grep -v sample | grep -v '^.$' | grep -v '^..$' | grep -v '^.git$'| xargs git rm -rf

	exec git add -A include shaders sample
	
	echo git commit -m "Generated: $COMMIT_ID"
	git commit -m "Generated: $COMMIT_ID"
	
	exec git checkout master

	echo git merge --allow-unrelated-histories $BRANCH_NAME -m "Generated: $COMMIT_ID"
	if git merge --allow-unrelated-histories $BRANCH_NAME -m "Generated: $COMMIT_ID"; then
		echo "There is no update. checkout to $COMMIT_ID"
		exec git reset --hard HEAD^
		exec git checkout $COMMIT_ID
	else
		exec git checkout --theirs .
		exec git add -A .
		
		echo git commit -m "Generated: $COMMIT_ID"
		git commit -m "Generated: $COMMIT_ID"
	fi
)
