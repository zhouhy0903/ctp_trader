
struct CThostFtdcInvestorPositionField
{
	///ºÏÔ¼´úÂë
	TThostFtdcInstrumentIDType	InstrumentID;
	///¾­¼Í¹«Ë¾´úÂë
	TThostFtdcBrokerIDType	BrokerID;
	///Í¶×ÊÕß´úÂë
	TThostFtdcInvestorIDType	InvestorID;
	///³Ö²Ö¶à¿Õ·½Ïò
	TThostFtdcPosiDirectionType	PosiDirection;
	///Í¶»úÌ×±£±êÖ¾
	TThostFtdcHedgeFlagType	HedgeFlag;
	///³Ö²ÖÈÕÆÚ
	TThostFtdcPositionDateType	PositionDate;
	///ÉÏÈÕ³Ö²Ö
	TThostFtdcVolumeType	YdPosition;
	///½ñÈÕ³Ö²Ö
	TThostFtdcVolumeType	Position;
	///¶àÍ·¶³½á
	TThostFtdcVolumeType	LongFrozen;
	///¿ÕÍ·¶³½á
	TThostFtdcVolumeType	ShortFrozen;
	///¿ª²Ö¶³½á½ð¶î
	TThostFtdcMoneyType	LongFrozenAmount;
	///¿ª²Ö¶³½á½ð¶î
	TThostFtdcMoneyType	ShortFrozenAmount;
	///¿ª²ÖÁ¿
	TThostFtdcVolumeType	OpenVolume;
	///Æ½²ÖÁ¿
	TThostFtdcVolumeType	CloseVolume;
	///¿ª²Ö½ð¶î
	TThostFtdcMoneyType	OpenAmount;
	///Æ½²Ö½ð¶î
	TThostFtdcMoneyType	CloseAmount;
	///³Ö²Ö³É±¾
	TThostFtdcMoneyType	PositionCost;
	///ÉÏ´ÎÕ¼ÓÃµÄ±£Ö¤½ð
	TThostFtdcMoneyType	PreMargin;
	///Õ¼ÓÃµÄ±£Ö¤½ð
	TThostFtdcMoneyType	UseMargin;
	///¶³½áµÄ±£Ö¤½ð
	TThostFtdcMoneyType	FrozenMargin;
	///¶³½áµÄ×Ê½ð
	TThostFtdcMoneyType	FrozenCash;
	///¶³½áµÄÊÖÐø·Ñ
	TThostFtdcMoneyType	FrozenCommission;
	///×Ê½ð²î¶î
	TThostFtdcMoneyType	CashIn;
	///ÊÖÐø·Ñ
	TThostFtdcMoneyType	Commission;
	///Æ½²ÖÓ¯¿÷
	TThostFtdcMoneyType	CloseProfit;
	///³Ö²ÖÓ¯¿÷
	TThostFtdcMoneyType	PositionProfit;
	///ÉÏ´Î½áËã¼Û
	TThostFtdcPriceType	PreSettlementPrice;
	///±¾´Î½áËã¼Û
	TThostFtdcPriceType	SettlementPrice;
	///½»Ò×ÈÕ
	TThostFtdcDateType	TradingDay;
	///½áËã±àºÅ
	TThostFtdcSettlementIDType	SettlementID;
	///¿ª²Ö³É±¾
	TThostFtdcMoneyType	OpenCost;
	///½»Ò×Ëù±£Ö¤½ð
	TThostFtdcMoneyType	ExchangeMargin;
	///×éºÏ³É½»ÐÎ³ÉµÄ³Ö²Ö
	TThostFtdcVolumeType	CombPosition;
	///×éºÏ¶àÍ·¶³½á
	TThostFtdcVolumeType	CombLongFrozen;
	///×éºÏ¿ÕÍ·¶³½á
	TThostFtdcVolumeType	CombShortFrozen;
	///ÖðÈÕ¶¢ÊÐÆ½²ÖÓ¯¿÷
	TThostFtdcMoneyType	CloseProfitByDate;
	///Öð±Ê¶Ô³åÆ½²ÖÓ¯¿÷
	TThostFtdcMoneyType	CloseProfitByTrade;
	///½ñÈÕ³Ö²Ö
	TThostFtdcVolumeType	TodayPosition;
	///±£Ö¤½ðÂÊ
	TThostFtdcRatioType	MarginRateByMoney;
	///±£Ö¤½ðÂÊ(°´ÊÖÊý)
	TThostFtdcRatioType	MarginRateByVolume;
	///Ö´ÐÐ¶³½á
	TThostFtdcVolumeType	StrikeFrozen;
	///Ö´ÐÐ¶³½á½ð¶î
	TThostFtdcMoneyType	StrikeFrozenAmount;
	///·ÅÆúÖ´ÐÐ¶³½á
	TThostFtdcVolumeType	AbandonFrozen;
	///½»Ò×Ëù´úÂë
	TThostFtdcExchangeIDType	ExchangeID;
	///Ö´ÐÐ¶³½áµÄ×ò²Ö
	TThostFtdcVolumeType	YdStrikeFrozen;
	///Í¶×Êµ¥Ôª´úÂë
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///´óÉÌËù³Ö²Ö³É±¾²îÖµ£¬Ö»ÓÐ´óÉÌËùÊ¹ÓÃ
	TThostFtdcMoneyType	PositionCostOffset;
	///tas³Ö²ÖÊÖÊý
	TThostFtdcVolumeType	TasPosition;
	///tas³Ö²Ö³É±¾
	TThostFtdcMoneyType	TasPositionCost;
}
