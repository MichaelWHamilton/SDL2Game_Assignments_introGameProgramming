<h1>SDL2 Project</h1>
<p>
SDL2 Project with emphasize on object oriented programming. This project serves to explore object oriented programming while utilizing SDL2 and Box2D.
</p>
<h3>Game Engine</h3>
<p>
Manages sdl, stores all gameobjects and updates them accordingly, keeps up with a camera state that tracks the main player and will store and update the box2d game world.
</p>
<h3>Textures</h3>
<p>
  Textures class handles loading all textures with a name and path from a JSON file. They are stored in a map with their name being the keys for the textures.
</p>
<h3>Game Objects</h3>
<p>
  GameObjectLoader handles loading all gameObjects and their components from a JSON file and stores them in a map in the engine class.
</p>
<h3>Component System</h3>
<p>
  The component system that allows for the dynamic addition of components to gameObjects. Components are different systems or behaviors a game object may have. Some comopnents will maintain information about the game object such as body, character controller others are behaviors and modify the body componet such as a follow component, or a move up and down component.
</p>
