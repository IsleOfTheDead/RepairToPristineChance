class CfgPatches
{
  class RepairToPristineChance
  {
    units[]={};
    weapons[]={};
    requiredVersion=0.1;
    requiredAddons[]={ "DZ_Scripts" };
  };
};

class CfgMods
{
  class RepairToPristineChance
  {
    dir="RepairToPristineChance";
    hideName=0;
    hidePicture=0;
    extra=0;
    name="RepairToPristineChance";
    picture="RepairToPristineChance\data\picture.paa";
    logoSmall="RepairToPristineChance\data\logoSmall.paa";
    logo="RepairToPristineChance\data\logo.paa";
    logoOver="RepairToPristineChance\data\logo.paa";
    action="https://steamcommunity.com/sharedfiles/filedetails/?id=3638002113";
    credits="moldypenguins";
    author="moldypenguins";
    authorID="76561198312711389";
    version="1.2";
    type="mod";
    dependencies[]={ "World" };
    class defs
    {
      class engineScriptModule
      {
        value="";
        files[]={ "RepairToPristineChance\scripts\1_core" };
      };
      class worldScriptModule
      {
        value="";
        files[]={ "RepairToPristineChance\scripts\4_world" };
      };
    }
  };
};
