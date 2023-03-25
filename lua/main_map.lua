return {
  version = "1.10",
  luaversion = "5.1",
  tiledversion = "1.10.0",
  class = "",
  orientation = "orthogonal",
  renderorder = "right-down",
  width = 70,
  height = 46,
  tilewidth = 32,
  tileheight = 32,
  nextlayerid = 8,
  nextobjectid = 1,
  properties = {},
  tilesets = {
    {
      name = "main_spritesheet",
      firstgid = 1,
      filename = "../res/images/main_spritesheet.tsx",
      exportfilename = "main_spritesheet.lua"
    },
    {
      name = "dg_grounds32",
      firstgid = 6081,
      filename = "../res/images/dg_grounds32.tsx",
      exportfilename = "dg_grounds32.lua"
    }
  },
  layers = {
    {
      type = "tilelayer",
      x = 0,
      y = 0,
      width = 70,
      height = 46,
      id = 1,
      name = "background",
      class = "",
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      parallaxx = 1,
      parallaxy = 1,
      properties = {
        ["start_tile"] = "new_new"
      },
      encoding = "lua",
      data = {
        590, 589, 589, 589, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 594, 594, 594, 594, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        589, 589, 589, 589, 589, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 594, 594, 594, 594, 594, 594, 594, 594, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        589, 589, 589, 589, 589, 590, 590, 589, 589, 590, 590, 590, 590, 590, 594, 594, 594, 594, 594, 594, 594, 594, 594, 594, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 589, 589, 589, 590, 590, 590, 590, 590, 592, 592, 590, 594, 594, 594, 594, 594, 594, 594, 594, 594, 594, 594, 594, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 589, 589, 590, 590, 590, 590, 590, 592, 594, 592, 592, 594, 594, 594, 594, 594, 594, 594, 594, 594, 594, 594, 594, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 592, 592, 594, 6124, 594, 594, 594, 594, 594, 594, 594, 594, 594, 594, 594, 594, 594, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 589, 590, 590, 590, 589, 589, 594, 594, 6124, 6124, 6124, 594, 594, 594, 594, 594, 594, 594, 594, 594, 594, 594, 594, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 589, 590, 589, 589, 592, 592, 594, 6124, 594, 594, 594, 594, 594, 594, 594, 594, 594, 594, 594, 594, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 592, 594, 592, 594, 594, 594, 594, 590, 590, 594, 594, 594, 594, 594, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 594, 594, 594, 590, 590, 590, 590, 590, 590, 594, 594, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 6108, 6108, 6108, 6108, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 589, 590, 590, 590, 590, 590, 590, 588, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 6108, 6108, 6108, 6108, 6108, 6108, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 589, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 6108, 6108, 6108, 6108, 6108, 6108, 6108, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 6108, 6108, 6108, 6108, 6108, 6108, 6108, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 6108, 6108, 6108, 6108, 6108, 6108, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 589, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 6108, 6108, 6108, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 589, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 6153, 6153, 6153, 6153, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        588, 590, 590, 590, 589, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 6153, 6153, 6154, 6154, 6153, 6153, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 589, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 6153, 6154, 6154, 6154, 6154, 6153, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 589, 589, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 6153, 6153, 6154, 6154, 6153, 6153, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 6153, 6153, 6153, 6153, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 589, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 589, 590, 590, 590, 590, 590, 590, 594, 594, 594, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 589, 590, 590, 590, 590, 590, 594, 594, 592, 594, 594, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 594, 594, 594, 594, 594, 594, 594, 594, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 594, 594, 592, 594, 594, 594, 594, 592, 594, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 594, 594, 594, 594, 592, 594, 594, 594, 594, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 594, 594, 592, 594, 594, 594, 594, 590, 590, 590, 590, 590, 590, 590, 590, 590, 589, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 594, 594, 594, 592, 594, 590, 590, 590, 590, 590, 589, 589, 589, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 594, 594, 594, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590,
        590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590
      }
    },
    {
      type = "tilelayer",
      x = 0,
      y = 0,
      width = 70,
      height = 46,
      id = 2,
      name = "middleground",
      class = "",
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      parallaxx = 1,
      parallaxy = 1,
      properties = {},
      encoding = "lua",
      data = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3786, 0, 0, 0, 0, 919, 919, 919, 919, 919, 0, 0, 0, 0, 853, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 850, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 919, 0, 0, 0, 919, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 258, 258, 258, 258, 258, 258, 258, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 919, 0, 0, 0, 919, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 258, 258, 258, 258, 258, 258, 258, 258, 258, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 3782, 0, 0, 0, 0, 0, 0, 3971, 0, 0, 0, 0, 0, 0, 919, 0, 0, 0, 919, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 846, 0, 0, 0, 0, 919, 919, 701, 919, 919, 850, 0, 0, 848, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 846, 0, 0, 846, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 258, 258, 258, 258, 258, 258, 258, 258, 258, 258, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 850, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 846, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 258, 258, 258, 258, 258, 258, 258, 258, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 849, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 258, 258, 258, 258, 258, 258, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 846, 0, 0, 0, 0, 0, 0, 0, 0, 849, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 258, 258, 258, 258, 258, 258, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 848, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 258, 258, 258, 258, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 847, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1218, 1218, 1218, 1218, 1218, 1218, 1218, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1218, 0, 0, 0, 0, 0, 1218, 0, 0, 0, 0, 0, 0, 0, 847, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1218, 0, 782, 0, 782, 0, 1218, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1218, 0, 0, 0, 0, 0, 1218, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1217, 1217, 1220, 1220, 1220, 1220, 1220, 1220, 1221, 1220, 1220, 1220, 1220, 1217, 1217, 1217, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1218, 1218, 1218, 1218, 1218, 1218, 1218, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1219, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1217, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1217, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1218, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1220, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1220, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1217, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1217, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1220, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1220, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1220, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1220, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1217, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1217, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1220, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1217, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1220, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1220, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1220, 1220, 1220, 1220, 1220, 1221, 1221, 1222, 1222, 1222, 1222, 1221, 1221, 1220, 1220, 1220, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
      }
    },
    {
      type = "tilelayer",
      x = 0,
      y = 0,
      width = 70,
      height = 46,
      id = 7,
      name = "foreground",
      class = "",
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      parallaxx = 1,
      parallaxy = 1,
      properties = {},
      encoding = "lua",
      data = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 1642, 0, 1642, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1360, 0, 1360, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 1642, 0, 1642, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1360, 0, 0, 0, 0, 0, 1360, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
      }
    }
  }
}
