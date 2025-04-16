git add .
read -p "Enter commit message: " commit_message
git commit -m "$commit_message"
git pull
git push -u origin main