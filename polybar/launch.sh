kill -9 $(pgrep polybar)
kill  $(pgrep music-roll)
while pgrep -u $UID -x polybar >/dev/null; do sleep 1; done

# Launch bar1 and bar2
polybar example &
echo "Bar launched..."
