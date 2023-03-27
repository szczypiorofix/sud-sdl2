return {
  version = "1.10",
  luaversion = "5.1",
  tiledversion = "1.10.0",
  class = "",
  orientation = "orthogonal",
  renderorder = "right-down",
  width = 20,
  height = 12,
  tilewidth = 32,
  tileheight = 32,
  nextlayerid = 12,
  nextobjectid = 15,
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
      width = 20,
      height = 12,
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
        594, 594, 592, 592, 592, 592, 592, 592, 592, 592, 592, 592, 592, 592, 592, 592, 592, 592, 592, 596,
        594, 592, 592, 594, 592, 592, 594, 594, 594, 594, 594, 594, 594, 594, 594, 594, 592, 596, 592, 592,
        592, 594, 592, 594, 594, 592, 592, 594, 911, 913, 914, 912, 914, 911, 913, 594, 592, 592, 592, 592,
        592, 592, 592, 592, 594, 592, 592, 594, 912, 592, 592, 592, 592, 592, 913, 594, 592, 592, 592, 596,
        592, 592, 592, 592, 592, 592, 592, 594, 912, 592, 592, 592, 592, 592, 911, 594, 596, 592, 592, 596,
        592, 592, 592, 592, 594, 592, 594, 592, 913, 592, 592, 592, 592, 592, 912, 594, 592, 592, 592, 596,
        592, 592, 592, 592, 592, 594, 592, 592, 911, 592, 592, 592, 596, 592, 914, 594, 596, 592, 592, 592,
        592, 621, 623, 623, 619, 592, 592, 594, 911, 914, 911, 592, 911, 912, 911, 594, 592, 592, 592, 592,
        592, 631, 617, 617, 625, 592, 592, 594, 592, 592, 592, 592, 592, 596, 592, 592, 592, 596, 592, 592,
        592, 631, 617, 597, 592, 592, 592, 592, 592, 592, 592, 596, 592, 592, 592, 592, 592, 592, 592, 596,
        592, 627, 629, 625, 592, 592, 592, 596, 592, 596, 592, 596, 596, 592, 592, 592, 592, 592, 596, 596,
        592, 592, 592, 592, 592, 592, 592, 592, 592, 592, 592, 592, 596, 596, 592, 592, 592, 596, 596, 596
      }
    },
    {
      type = "tilelayer",
      x = 0,
      y = 0,
      width = 20,
      height = 12,
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
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 847, 848, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 782, 0, 0, 0, 0, 0, 0, 0, 787, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 846, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 847, 0, 0,
        0, 0, 846, 847, 848, 0, 0, 0, 0, 80, 0, 0, 0, 80, 0, 0, 847, 847, 848, 0,
        0, 0, 0, 848, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 847, 848, 847, 0,
        0, 0, 0, 846, 0, 847, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 847, 848, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 847, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1360, 0, 1360, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 782, 0, 0, 0, 0, 0, 0, 0, 785, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 846, 0, 0, 0, 0, 846, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
      }
    },
    {
      type = "objectgroup",
      draworder = "topdown",
      id = 8,
      name = "objects",
      class = "",
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      parallaxx = 1,
      parallaxy = 1,
      properties = {},
      objects = {
        {
          id = 14,
          name = "portal",
          type = "",
          shape = "rectangle",
          x = 352,
          y = 256,
          width = 32,
          height = 32,
          rotation = 0,
          gid = 915,
          visible = true,
          properties = {}
        }
      }
    },
    {
      type = "imagelayer",
      image = "",
      id = 11,
      name = "Image Layer 1",
      class = "",
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      parallaxx = 1,
      parallaxy = 1,
      repeatx = false,
      repeaty = false,
      properties = {}
    }
  }
}
