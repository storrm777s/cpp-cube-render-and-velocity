Creates and draws rectangles which are formed via points, made as general C++ practice.

A lot of this is messy and unorganized, as many things were added randomly. Originally this was meant to only render a rectangle, then I wanted to make it fall, then I wanted to make it rotate, etc.

abcd are used as points, a being top left, b being top right, c being bottom right, and d being bottom left.
v is used for velocity, r is used for rotation, rv is used for rotation velocity.

abcd as seen in StructRectangle and here:
```
Vector2({a1,a2}, {b1,b2}, {c1,c2}, {d1,d2});
```
```
StructRectangle rect = Rectangle(
	x,y,      //a
	x+50,y,     //b
	x+50,y+50,    //c
	x,y+50,     //d
	0,-10,      //v
	90,          //r
	0.01          //rv
);
```

Velocity handling:
```
for (int i = 0; i < 5; i++) {
	rect.pos.points[i].x += rect.velocity.x * dt;
	rect.pos.points[i].y += rect.velocity.y * dt;
}
```

This is used to rotate the rectangle, I don't understand the math well here.
```
float dx = rect.pos.points[i].x - rect.center.x;
float dy = rect.pos.points[i].y - rect.center.y;

rect.pos.points[i].x = dx * cos(rect.rotationvelocity) - dy * sin(rect.rotationvelocity) + rect.center.x;
rect.pos.points[i].y = dx * sin(rect.rotationvelocity) + dy * cos(rect.rotationvelocity) + rect.center.y;
```


Originally compiled with:
```
"-fdiagnostics-color=always",
"-Iinclude",
"-g",
"-Wall",
"main.cpp",
// "src/*.cpp",
"-lsfml-graphics",
"-lsfml-window",
"-lsfml-system",
"-lsfml-audio",
"-o",
"main"
```
        
