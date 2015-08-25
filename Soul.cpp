
class npc_corrupted_soul_fragment : public CreatureScript
{
    public:
        npc_corrupted_soul_fragment() : CreatureScript("npc_corrupted_soul_fragment") { }

        struct npc_corrupted_soul_fragmentAI : public ScriptedAI
        {
            npc_corrupted_soul_fragmentAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = me->GetInstanceScript();
            }


			void UpdateAI(const uint32 diff)
			{
				if (instance)
				{
					if (Creature* pBronjham = ObjectAccessor::GetCreature(*me, instance->GetGuidData(DATA_BRONJAHM)))
					{
						if (pBronjham && pBronjham->IsAlive())
						{
							if (me->IsWithinMeleeRange(pBronjham))
							{
								pBronjham->CastSpell(pBronjham, SPELL_CONSUME_SOUL, true);
								//me->ForcedDespawn();
								me->DespawnOrUnsummon();
							}
							else
							{
								Position pos;
								//pBronjham->GetPosition(pos);'
								pos = pBronjham->GetPosition();
								me->GetMotionMaster()->Clear();
								//me->GetMotionMaster()->MoveChase(pBronjham, 1.0f);
								me->GetMotionMaster()->MovePoint(0, pos);
							}
						}
						else
							//me->ForcedDespawn();
							me->DespawnOrUnsummon();
					}
					//uiCheckTimer = 500;
				}
			}
				//else
				//	uiCheckTimer -= diff;

        private:
            InstanceScript* instance;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetInstanceAI<npc_corrupted_soul_fragmentAI>(creature, FoSScriptName);
        }
};
