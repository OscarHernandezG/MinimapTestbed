# Minimap

Research about how to implement a minimap in your game


“I am [Óscar Hernández](https://www.linkedin.com/in/oscar-hernandez-73b224161), student of the
[Bachelor’s Degree in Video Games by UPC at CITM](https://www.citm.upc.edu/ing/estudis/graus-videojocs).
This content is generated for the second year’s subject Project 2, under supervision of lecturer
[Ricard Pillosu](https://es.linkedin.com/in/ricardpillosu).”

## What is a minimap

A minimap is a miniature map that is usually placed at a corner of the screen to help players orient thmselves and manage to control what's happening outside his field of view. In a minimap the common features are the entities position (maybe only player entities or player and enemy entities) and objectives nearby as well as the sorrounding topography.

## How to implement a minimap

I have prepared a HandOut so you can follow step by step and learn how to implement a minimap for your videogame.
You can download the HandOut [here](https://github.com/OscarHernandezG/MinimapTestbed/archive/HandOut.zip)

### Todo 1
Set minimap info

The variables to set are 
```
SDL_Rect minimapInfo 
int entityWidth	
int entityHeight
```
Your code after this todo should look like this 
![Todo 1](https://github.com/OscarHernandezG/MinimapTestbed/blob/master/docs/images/todo1.png)
### Todo 2

- Save map into a texture </br>

- 2.1 Compute the scale factor for the Minimap.</br>
```
     scaleFactor = minimapSiz / emapSize
```
- 2.2 Create a RGB surface</br>
Use:
```
SDL_CreateRGBSurface()
```
The size of the surface is the size of the minimap

- 2.3 Create a renderer using the surface</br>
```
SDL_CreateSoftwareRenderer()
```
- 2.4 Read the renderer pixels </br>
Use:
```
SDL_RenderReadPixels()
```
- 2.5 Create a texture from the surface </br>
Use
```
SDL_CreateTextureFromSurface()
```
Your code after this todo should look like this 
![Todo 2](https://github.com/OscarHernandezG/MinimapTestbed/blob/master/docs/images/todo2.png)

### Todo 3
- Draw the map
Use your game blit function, you have to use the texture created in the Todo 2


Your code after this todo should look like this 
![Todo 3](https://github.com/OscarHernandezG/MinimapTestbed/blob/master/docs/images/todo3.png)

And the game should look like this
![Todo 3 done](https://github.com/OscarHernandezG/MinimapTestbed/blob/master/docs/images/todo3_done.png)

### Todo 4
- Draw all entities in the minimap
The minimap has a list of pointers to entity, all the entities that you want to be showed in the minimap has to be added to this list
To draw the entities we blit quads, so we don´t have to load more textures 

Your code after this todo should look like this 
![Todo 4](https://github.com/OscarHernandezG/MinimapTestbed/blob/master/docs/images/todo4.png)

And the game should look like this
![Todo 4 done](https://github.com/OscarHernandezG/MinimapTestbed/blob/master/docs/images/todo4_done.png)

### Todo 5
- Draw the camera rect
The player will want to know were he is, to accomplish this we draw another quad in the camera position and with the camera size, but we don´t fill the rect. If we fill the rect the player won´t be able to see the minimap!

Your code after this todo should look like this 
![Todo 5](https://github.com/OscarHernandezG/MinimapTestbed/blob/master/docs/images/todo5.png)

And the game should look like this
![Todo 5 done](https://github.com/OscarHernandezG/MinimapTestbed/blob/master/docs/images/todo5_done.png)

### Extra Todo
- Implement a Fow of War system to make the minimap more interesting

## Future
As said in [this](https://kotaku.com/video-game-mini-maps-might-finally-be-going-away-1820011897) article, minimaps might be going to disapear. In many recent videogames the minimap is gone, and it dosen't feel like is missing.


## References
[Minimaps](https://en.wikipedia.org/wiki/Mini-map)
[Minimaps might be going away](https://kotaku.com/video-game-mini-maps-might-finally-be-going-away-1820011897)
