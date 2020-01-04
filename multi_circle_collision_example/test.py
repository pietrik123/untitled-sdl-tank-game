obstacle_circles = [(50,120,32),
(55,73,32),
(47,50,32),
(87,55,32),
(120,67,32),
(118,122,32),
(131,132,32),
(75,150,32),
(96,144,32)]

player_circles = [
(-22,47,37),
(13,41,37),
(183,31,37),
(85,96,37),
(203,164,37)]

def are_circles_intersecting(x1,y1,r1,x2,y2,r2):
    return (((x2-x1)**2.0 + (y2-y1)**2.0)**0.5 <= r1 + r2)
    
def is_collision(x1,y1,r1,obstacle_circles):
    for o in obstacle_circles:
        if are_circles_intersecting(x1,y1,r1,o[0],o[1],o[2]):
            return True
    return False
    
for o in obstacle_circles:
   print( "{} {} {}\n".format(o[0],o[1],o[2]))
   
print ("--------------")

cnt = 1
for pc in player_circles:
    if is_collision(pc[0],pc[1],pc[2],obstacle_circles):
        print("{} : COLISSION YES : x={}, y={} r={}".format(cnt, pc[0],pc[1],pc[2]))
    else:
        print("{} : COLISSION NO".format(cnt))
    cnt+=1