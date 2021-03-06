
function createImage(texture_name, char_size)
	local gfxQuad = MOAIGfxQuad2D.new()
	gfxQuad:setTexture(texture_name)
    if char_size == nil then
        char_size = 64
    end
	gfxQuad:setRect(-char_size/2, -char_size/2, char_size/2, char_size/2)
	gfxQuad:setUVRect(0, 0, 1, 1)
	return gfxQuad
end

MOAISim.openWindow("game", 1024, 768)

viewport = MOAIViewport.new()
viewport:setSize (1024, 768)
viewport:setScale (1024, -768)

layer = MOAILayer2D.new()
layer:setViewport(viewport)
MOAISim.pushRenderPass(layer)

--Texture of enemy character


gfxQuad = createImage("mago.png", 32)
gfxQuad1 = createImage("skeleton.png", 32)

prop = MOAIProp2D.new()
prop:setDeck(gfxQuad)
enemy = Character.new()

-- Add prop to be the renderable for this character
enemy:addImage(gfxQuad)    -- SetImage(0)  alive
enemy:addImage(gfxQuad1)   -- SetImage(1)  death

-- Add prop to be the renderable for this character
enemy:setProp(prop, layer)
enemy:checkIsEnemy(true)
-- Start the character (allow calls to OnUpdate)
enemy:start()
enemy:setLoc(-400, 0)
enemy:setRot(0)
enemy:setLinearVel(100, 0)
--entity:setAngularVel(30)

--Texture of dragon character
gfxQuad = createImage("dragon_idle.png", 64)
gfxQuad1 = createImage("dragon_alarm.png", 64)
gfxQuad2 = createImage("dragon_windup.png", 64)
gfxQuad3 = createImage("dragon_attack.png", 64)

prop = MOAIProp2D.new()
prop:setDeck(gfxQuad)
entity  = Character.new()

-- Add prop to be the renderable for this character
entity:addImage(gfxQuad)    -- SetImage(0)  idle
entity:addImage(gfxQuad1)   -- SetImage(1)  alert
entity:addImage(gfxQuad2)   -- SetImage(2)  windup
entity:addImage(gfxQuad3)   -- SetImage(3)  attack

-- Add prop to be the renderable for this character
entity:setProp(prop, layer)
entity:checkIsEnemy(false, enemy);
-- Start the character (allow calls to OnUpdate)
entity:start()
entity:setLoc(-200, 0)
entity:setRot(0)
entity:setLinearVel(0, 0)
--entity:setAngularVel(30)

-- Enable Debug Draw
debug = MOAIDrawDebug.get();
layer:setDrawDebug(debug)
-- Add this character to draw debug
MOAIDrawDebug.insertEntity(entity)
MOAIDrawDebug.insertEntity(enemy);

mouseX = 0
mouseY = 0

function onClick(down)
  enemy:setLoc(mouseX, mouseY)
  entity:setRot(0)
end

function pointerCallback(x, y)
    mouseX, mouseY = layer:wndToWorld(x, y)
end

MOAIInputMgr.device.mouseLeft:setCallback(onClick)
MOAIInputMgr.device.pointer:setCallback(pointerCallback)