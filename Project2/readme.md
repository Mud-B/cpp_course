```flow
st=>start: Start
opt=>inputoutput: Deal user input option
file=>inputoutput: Read file input
goal=>condition: Reach the goal?
getpose=>operation: Get robot current position
getwp=>operation: Get closet waypoints index

cmd=>inputoutput: Compute and send velocity cmd 
end=>end: End

st->opt
opt->file
```