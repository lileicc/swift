git pull -all
git remote prune origin
git branch --merged | grep -v "\*" | xargs -n 1 git branch -d
git pull
git push
