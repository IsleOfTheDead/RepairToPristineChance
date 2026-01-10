modded class PluginRepairing
{
  //TODO: IOTD - Fix this file so changes are more apparent.
  override void CalculateHealth(PlayerBase player, ItemBase kit, Object item, float specialty_weight, string damage_zone = "", bool use_kit_qty = true) {
    EntityAI entity;
    Class.CastTo(entity, item);
    if (entity != null)
    {
      entity.SetAllowDamage(true);
    }
    int health_levels_count = item.GetNumberOfHealthLevels(damage_zone);
    float kit_repair_cost_adjusted; //used with specialty_weight, disconnected
    float new_quantity;
    int current_level = item.GetHealthLevel(damage_zone);
    int target_level = Math.Clamp(Math.Clamp(current_level - 1, 0, health_levels_count - 1), GameConstants.STATE_PRISTINE, health_levels_count - 1).ToInt();
    float health_coef = item.GetHealthLevelValue(target_level, damage_zone);
    //handles kit depletion; TODO: move to separate method.
    if (kit && kit.ConfigGetInt("repairKitType"))
    {
      bool kit_has_quantity = kit.HasQuantity();
      float cur_kit_quantity = kit.GetQuantity();
      float kit_repair_cost_per_level = GetKitRepairCost(kit, item);
      if (cur_kit_quantity > kit_repair_cost_per_level)
      {
        kit_repair_cost_adjusted = kit_repair_cost_per_level; //TODO: removed speciality weight for now, it should affect speed only (?).
        //kit_repair_cost_adjusted = player.GetSoftSkillsManager().SubtractSpecialtyBonus(kit_repair_cost_per_level, specialty_weight);
        kit_repair_cost_adjusted = Math.Clamp(kit_repair_cost_adjusted, 0, 100);
        if (use_kit_qty)
        {
          new_quantity = kit.GetQuantity() - kit_repair_cost_adjusted;
          kit.SetQuantity(new_quantity);
        }
      }
      else if (!kit_has_quantity) //"kit" without quantity (hammers and such) for your every day repairing needs
      {}
      else
      {
        if (use_kit_qty) {
          kit.SetQuantity(0);
        }
      }
    }
    // check if repair chance was successful
    if ((Math.RandomInt(0, 100) <= 33 && current_level >= GameConstants.STATE_WORN) || current_level >= GameConstants.STATE_DAMAGED)
    {
      if (item.GetHealth01(damage_zone, "Health") < health_coef)
      {
        item.SetHealth01(damage_zone, "Health", health_coef);
      }
    }
    if (entity != null)
    {
      entity.ProcessInvulnerabilityCheck(entity.GetInvulnerabilityTypeString());
    }
  }

  override bool CanRepair(ItemBase repair_kit, Object item, string damage_zone = "")
  {
    int state = item.GetHealthLevel(damage_zone);
    if (state != GameConstants.STATE_RUINED && state != GameConstants.STATE_PRISTINE)
    {
      int repair_kit_type = repair_kit.ConfigGetInt("repairKitType");
      if (!repair_kit_type) //outside of regular repair kit logic for some reason, bypass check
      {
        return true;
      }
      array<int> repairable_with_types = new array<int> ;
      item.ConfigGetIntArray("repairableWithKits", repairable_with_types);
      for (int i = 0; i < repairable_with_types.Count(); i++)
      {
        int repairable_with_type = repairable_with_types.Get(i);
        if (IsRepairValid(repair_kit_type, repairable_with_type))
        {
          return true;
        }
      }
    }
    return false;
  }

  //! Player can repair items to 100%; currently unused
  override private bool CanRepairToPristine(PlayerBase player)
  {
    //return false;
    return true;
  }

  //! Item can be repaired to 100%
  override private bool CanBeRepairedToPristine(Object item)
  {
    //return item.CanBeRepairedToPristine();
    return true;
  }

};
