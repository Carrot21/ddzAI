﻿
#include "GameAI_Config.h"
#include "GameAI_Strategy.h"
#include "GameAI_Algorithm.h"
#include "GameAI_GroupType.h"
/*�����ຯ��*/


/*1.0�汾���� �������� ��һ�������ƣ��������Ʋ��� */
void get_PutCardList_1(GameSituation&clsGameSituation, HandCardData&clsHandCardData)
{
	clsHandCardData.ClearPutCardList();
	if (clsGameSituation.nCardDroit == clsHandCardData.nOwnIndex)
	{
		
		clsHandCardData.value_nPutCardList.push_back(clsHandCardData.value_nHandCardList[0]);

		clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgSINGLE, clsHandCardData.value_nHandCardList[0], 1);
		
	}	
	else
	{
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
	}
	return;
}



/*
2.0�汾���� ���غ�����ֻ���ڼ����Լ�������Ҫ�����ִο��Գ��꼴��Ȩֵ��� 
*/
void get_PutCardList_2(HandCardData &clsHandCardData)
{
	
	clsHandCardData.ClearPutCardList();

	//��֦������ܳ�ȥ���һ����ֱ�ӳ�
	CardGroupData SurCardGroupData = ins_SurCardsType(clsHandCardData.value_aHandCardList);
	//�����һ���Գ�ȥ��û��ը������Ϊ��ը���Ļ�Ȩֵ���ܻ����
	if (SurCardGroupData.cgType != cgERROR&&!HasBoom(clsHandCardData.value_aHandCardList))
	{
			Put_All_SurCards(clsHandCardData, SurCardGroupData);
			return;
	}

	/*��ը������ǰ����ֻ������ը��Ϊ�����ڶ��ֵ����ȳ����߼��������汾���ڴ˻������Ż�*/
	if (clsHandCardData.value_aHandCardList[17] > 0 && clsHandCardData.value_aHandCardList[16] > 0)
	{

		clsHandCardData.value_aHandCardList[17] --;
		clsHandCardData.value_aHandCardList[16] --;
		clsHandCardData.nHandCardCount -= 2;
		HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
		clsHandCardData.value_aHandCardList[16] ++;
		clsHandCardData.value_aHandCardList[17] ++;
		clsHandCardData.nHandCardCount += 2;
		if (tmpHandCardValue.NeedRound == 1)
		{
			clsHandCardData.value_nPutCardList.push_back(17);
			clsHandCardData.value_nPutCardList.push_back(16);
			clsHandCardData.uctPutCardType = get_GroupData(cgKING_CARD, 17, 2);
			return;
		}
	}

	//�ݴ���ѵļ�ֵ
	HandCardValue BestHandCardValue;
	BestHandCardValue.NeedRound = 20;
	BestHandCardValue.SumValue = MinCardsValue;
	//������Ϊ�����ƵĻ����ö���һ���ִΣ�����һ�֣�Ȩֵ����7�����ں����ĶԱȲο���
	BestHandCardValue.NeedRound += 1;

	//�ݴ���ѵ����
	CardGroupData BestCardGroup;

	//����ȥ����
	int tmp_1 = 0;
	int tmp_2 = 0;
	int tmp_3 = 0;
	int tmp_4 = 0;

	/*
	���ȴ������ơ��ɻ����ƣ���Ϊ�������Ϳ��԰�С�ƴ���,��ʵ����ԱȽϴ������һ���Ǻܹ�ƽ
	�����汾�����ڴ˴�����֧��������˵����һ�Ļ�ֻѭ����10��J�����Ȳ��ż������
	*/
	for (int i = 3; i < 16; i++)
	{
		//2.0�汾�����������Ʋ����ը�������Լ������Ͳ����Ĵ�������Ϊ��
		if (clsHandCardData.value_aHandCardList[i] != 4)
		{
			//������һ
			if (clsHandCardData.value_aHandCardList[i] > 2)
			{
				clsHandCardData.value_aHandCardList[i] -= 3;
				for (int j = 3; j < 18; j++)
				{
					if (clsHandCardData.value_aHandCardList[j] > 0 )
					{
						clsHandCardData.value_aHandCardList[j] -= 1;
						clsHandCardData.nHandCardCount -= 4;
						HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
						clsHandCardData.value_aHandCardList[j] += 1;
						clsHandCardData.nHandCardCount += 4;
						//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
						if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
						{
							BestHandCardValue = tmpHandCardValue;
							BestCardGroup = get_GroupData(cgTHREE_TAKE_ONE, i, 4);
							tmp_1 = j;
						}
					}
				}
				clsHandCardData.value_aHandCardList[i] += 3;
			}
			//��������
			if (clsHandCardData.value_aHandCardList[i] > 2)
			{
				for (int j = 3; j < 16; j++)
				{
					clsHandCardData.value_aHandCardList[i] -= 3;
					if (clsHandCardData.value_aHandCardList[j] > 1)
					{
						clsHandCardData.value_aHandCardList[j] -= 2;
						clsHandCardData.nHandCardCount -= 5;
						HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
						clsHandCardData.value_aHandCardList[j] += 2;
						clsHandCardData.nHandCardCount += 5;
						//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
						if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
						{
							BestHandCardValue = tmpHandCardValue;
							BestCardGroup = get_GroupData(cgTHREE_TAKE_TWO, i, 5);
							tmp_1 = j;
						}
					}
					clsHandCardData.value_aHandCardList[i] += 3;
				}
			}
			//���Ĵ�����
			if (clsHandCardData.value_aHandCardList[i] > 3)
			{
				//2.0�汾�����������Ʋ����ը�������Լ������Ͳ����Ĵ�������Ϊ��
			}
			//���Ĵ�����
			if (clsHandCardData.value_aHandCardList[i] > 3)
			{
				//2.0�汾�����������Ʋ����ը�������Լ������Ͳ����Ĵ�������Ϊ��
			}
			//������һ����
			if (clsHandCardData.value_aHandCardList[i] > 2)
			{
				int prov = 0;
				for (int j = i; j < 15; j++)
				{
					if (clsHandCardData.value_aHandCardList[j] > 2)
					{
						prov++;
					}
					else
					{
						break;
					}
					/*��������ȫ����ѡȡ��������Ȼ��ö�ٳ���߼�ֵ�ģ������ǵ����ɻ�����Ҳ������2-4֮��
					���Ըɴ���������֧��������*/
					//Ϊ�����ɻ�
					if (prov == 2)
					{

						for (int k = i; k <= j; k++)
						{
							clsHandCardData.value_aHandCardList[k] -= 3;
						}
						clsHandCardData.nHandCardCount -= prov * 4;
						for (int tmp1 = 3; tmp1 < 18; tmp1++)
						{
							if (clsHandCardData.value_aHandCardList[tmp1] > 0 )
							{
								clsHandCardData.value_aHandCardList[tmp1] -= 1;
								for (int tmp2 = tmp1; tmp2 < 18; tmp2++)
								{
									if (clsHandCardData.value_aHandCardList[tmp2] > 0 )
									{
										clsHandCardData.value_aHandCardList[tmp2] -= 1;
										HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
									
										if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
										{
											BestHandCardValue = tmpHandCardValue;
											BestCardGroup = get_GroupData(cgTHREE_TAKE_ONE_LINE, j, prov * 4);
											tmp_1 = tmp1;
											tmp_2 = tmp2;

										}
										clsHandCardData.value_aHandCardList[tmp2] += 1;
									}
								}
								clsHandCardData.value_aHandCardList[tmp1] += 1;
							}
						}
						for (int k = i; k <= j; k++)
						{
							clsHandCardData.value_aHandCardList[k] += 3;
						}
						clsHandCardData.nHandCardCount += prov * 4;
					}
					//Ϊ�����ɻ�
					if (prov == 3)
					{
						for (int k = i; k <= j; k++)
						{
							clsHandCardData.value_aHandCardList[k] -= 3;
						}
						clsHandCardData.nHandCardCount -= prov * 4;
						for (int tmp1 = 3; tmp1 < 18; tmp1++)
						{
							if (clsHandCardData.value_aHandCardList[tmp1] > 0 )
							{
								clsHandCardData.value_aHandCardList[tmp1] -= 1;
								for (int tmp2 = tmp1; tmp2 < 18; tmp2++)
								{
									if (clsHandCardData.value_aHandCardList[tmp2] > 0 )
									{
										clsHandCardData.value_aHandCardList[tmp2] -= 1;
										for (int tmp3 = tmp2; tmp3 < 18; tmp3++)
										{
											if (clsHandCardData.value_aHandCardList[tmp3] > 0 )
											{
												clsHandCardData.value_aHandCardList[tmp3] -= 1;

												HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
												if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
												{

													BestHandCardValue = tmpHandCardValue;
													BestCardGroup = get_GroupData(cgTHREE_TAKE_ONE_LINE, j, prov * 4);
													tmp_1 = tmp1;
													tmp_2 = tmp2;
													tmp_3 = tmp3;

												}
												clsHandCardData.value_aHandCardList[tmp3] += 1;
											}

										}
										clsHandCardData.value_aHandCardList[tmp2] += 1;
									}

								}
								clsHandCardData.value_aHandCardList[tmp1] += 1;
							}
						}
						for (int k = i; k <= j; k++)
						{
							clsHandCardData.value_aHandCardList[k] += 3;
						}
						clsHandCardData.nHandCardCount += prov * 4;
					}
					//Ϊ�����ɻ�
					if (prov == 4)
					{
						for (int k = i; k <= j; k++)
						{
							clsHandCardData.value_aHandCardList[k] -= 3;
						}
						clsHandCardData.nHandCardCount -= prov * 4;
						for (int tmp1 = 3; tmp1 < 18; tmp1++)
						{
							if (clsHandCardData.value_aHandCardList[tmp1] > 0 )
							{
								clsHandCardData.value_aHandCardList[tmp1] -= 1;
								for (int tmp2 = tmp1; tmp2 < 18; tmp2++)
								{
									if (clsHandCardData.value_aHandCardList[tmp2] > 0 )
									{
										clsHandCardData.value_aHandCardList[tmp2] -= 1;
										for (int tmp3 = tmp2; tmp3 < 18; tmp3++)
										{
											if (clsHandCardData.value_aHandCardList[tmp3] > 0 )
											{
												clsHandCardData.value_aHandCardList[tmp3] -= 1;
												for (int tmp4 = tmp3; tmp4 < 18; tmp4++)
												{
													if (clsHandCardData.value_aHandCardList[tmp4] > 0 )
													{
														clsHandCardData.value_aHandCardList[tmp4] -= 1;
														HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
														if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
														{
															BestHandCardValue = tmpHandCardValue;
															BestCardGroup = get_GroupData(cgTHREE_TAKE_ONE_LINE, j, prov * 4);
															tmp_1 = tmp1;
															tmp_2 = tmp2;
															tmp_3 = tmp3;
															tmp_4 = tmp4;
														}
														clsHandCardData.value_aHandCardList[tmp4] += 1;
													}

												}
												clsHandCardData.value_aHandCardList[tmp3] += 1;
											}

										}
										clsHandCardData.value_aHandCardList[tmp2] += 1;
									}

								}
								clsHandCardData.value_aHandCardList[tmp1] += 1;
							}
						}
						for (int k = i; k <= j; k++)
						{
							clsHandCardData.value_aHandCardList[k] += 3;
						}
						clsHandCardData.nHandCardCount += prov * 4;
					}
					//��prov==5�����ǵ�������ֱ�ӳ�ȥ���ڼ�֦�����Ѿ�����
				}

			}
			//������һ˫��
			if (clsHandCardData.value_aHandCardList[i] > 2)
			{
				int prov = 0;
				for (int j = i; j < 15; j++)
				{
					if (clsHandCardData.value_aHandCardList[j] > 2 )
					{
						prov++;
					}
					else
					{
						break;
					}
					/*��������ȫ����ѡȡ��������Ȼ��ö�ٳ���߼�ֵ�ģ������ǵ����ɻ�����Ҳ������2-4֮��
					���Ըɴ���������֧��������*/
					//Ϊ�����ɻ�
					if (prov == 2)
					{

						for (int k = i; k <= j; k++)
						{
							clsHandCardData.value_aHandCardList[k] -= 3;
						}
						clsHandCardData.nHandCardCount -= prov * 5;
						for (int tmp1 = 3; tmp1 < 16; tmp1++)
						{
							if (clsHandCardData.value_aHandCardList[tmp1] > 1 )
							{
								clsHandCardData.value_aHandCardList[tmp1] -= 2;
								for (int tmp2 = tmp1; tmp2 < 16; tmp2++)
								{
									if (clsHandCardData.value_aHandCardList[tmp2] > 1 )
									{
										clsHandCardData.value_aHandCardList[tmp2] -= 2;
										HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
										if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
										{
											BestHandCardValue = tmpHandCardValue;
											BestCardGroup = get_GroupData(cgTHREE_TAKE_TWO_LINE, j, prov * 5);
											tmp_1 = tmp1;
											tmp_2 = tmp2;
										}
										clsHandCardData.value_aHandCardList[tmp2] += 2;
									}
								}
								clsHandCardData.value_aHandCardList[tmp1] += 2;
							}
						}
						for (int k = i; k <= j; k++)
						{
							clsHandCardData.value_aHandCardList[k] += 3;
						}
						clsHandCardData.nHandCardCount += prov * 5;
					}
					//Ϊ�����ɻ�
					if (prov == 3)
					{
						for (int k = i; k <= j; k++)
						{
							clsHandCardData.value_aHandCardList[k] -= 3;
						}
						clsHandCardData.nHandCardCount -= prov * 5;
						for (int tmp1 = 3; tmp1 < 16; tmp1++)
						{
							if (clsHandCardData.value_aHandCardList[tmp1] > 1 )
							{
								clsHandCardData.value_aHandCardList[tmp1] -= 2;
								for (int tmp2 = tmp1; tmp2 < 16; tmp2++)
								{
									if (clsHandCardData.value_aHandCardList[tmp2] > 1 )
									{
										clsHandCardData.value_aHandCardList[tmp2] -= 2;
										for (int tmp3 = tmp2; tmp3 < 16; tmp3++)
										{
											if (clsHandCardData.value_aHandCardList[tmp3] > 1 )
											{
												clsHandCardData.value_aHandCardList[tmp3] -= 2;
												HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
												if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
												{
													BestHandCardValue = tmpHandCardValue;
													BestCardGroup = get_GroupData(cgTHREE_TAKE_TWO_LINE, j, prov * 5);
													tmp_1 = tmp1;
													tmp_2 = tmp2;
													tmp_3 = tmp3;
												}
												clsHandCardData.value_aHandCardList[tmp3] += 2;
											}

										}
										clsHandCardData.value_aHandCardList[tmp2] += 2;
									}

								}
								clsHandCardData.value_aHandCardList[tmp1] += 2;
							}
						}
						for (int k = i; k <= j; k++)
						{
							clsHandCardData.value_aHandCardList[k] += 3;
						}
						clsHandCardData.nHandCardCount += prov * 5;
					}
					//��prov==4�����ǵ�������ֱ�ӳ�ȥ���ڼ�֦�����Ѿ�����
				}
			}
		}

	}
	if (BestCardGroup.cgType == cgTHREE_TAKE_ONE)
		{
			clsHandCardData.value_nPutCardList.push_back(BestCardGroup.nMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestCardGroup.nMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestCardGroup.nMaxCard);
			clsHandCardData.value_nPutCardList.push_back(tmp_1);
			clsHandCardData.uctPutCardType = BestCardGroup;
			return;
		}
	else if (BestCardGroup.cgType == cgTHREE_TAKE_TWO)
		{
			clsHandCardData.value_nPutCardList.push_back(BestCardGroup.nMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestCardGroup.nMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestCardGroup.nMaxCard);
			clsHandCardData.value_nPutCardList.push_back(tmp_1);
			clsHandCardData.value_nPutCardList.push_back(tmp_1);
			clsHandCardData.uctPutCardType = BestCardGroup;
			return;
		}
	else if (BestCardGroup.cgType == cgTHREE_TAKE_ONE_LINE)
		{
			for (int j = BestCardGroup.nMaxCard - (BestCardGroup.nCount / 4) + 1; j <= BestCardGroup.nMaxCard; j++)
			{
				clsHandCardData.value_nPutCardList.push_back(j);
				clsHandCardData.value_nPutCardList.push_back(j);
				clsHandCardData.value_nPutCardList.push_back(j);
			}

			if (BestCardGroup.nCount / 4 == 2)
			{
				clsHandCardData.value_nPutCardList.push_back(tmp_1);
				clsHandCardData.value_nPutCardList.push_back(tmp_2);
			}
			if (BestCardGroup.nCount / 4 == 3)
			{
				clsHandCardData.value_nPutCardList.push_back(tmp_1);
				clsHandCardData.value_nPutCardList.push_back(tmp_2);
				clsHandCardData.value_nPutCardList.push_back(tmp_3);
			}
			if (BestCardGroup.nCount / 4 == 4)
			{
				clsHandCardData.value_nPutCardList.push_back(tmp_1);
				clsHandCardData.value_nPutCardList.push_back(tmp_2);
				clsHandCardData.value_nPutCardList.push_back(tmp_3);
				clsHandCardData.value_nPutCardList.push_back(tmp_4);
			}

			clsHandCardData.uctPutCardType = BestCardGroup;
			return;
		}
	else if (BestCardGroup.cgType == cgTHREE_TAKE_TWO_LINE)
		{
			for (int j = BestCardGroup.nMaxCard - (BestCardGroup.nCount / 5) + 1; j <= BestCardGroup.nMaxCard; j++)
			{
				clsHandCardData.value_nPutCardList.push_back(j);
				clsHandCardData.value_nPutCardList.push_back(j);
				clsHandCardData.value_nPutCardList.push_back(j);
			}
			if (BestCardGroup.nCount / 5 == 2)
			{
				clsHandCardData.value_nPutCardList.push_back(tmp_1);
				clsHandCardData.value_nPutCardList.push_back(tmp_1);
				clsHandCardData.value_nPutCardList.push_back(tmp_2);
				clsHandCardData.value_nPutCardList.push_back(tmp_2);
			}
			if (BestCardGroup.nCount / 5 == 3)
			{
				clsHandCardData.value_nPutCardList.push_back(tmp_1);
				clsHandCardData.value_nPutCardList.push_back(tmp_1);
				clsHandCardData.value_nPutCardList.push_back(tmp_2);
				clsHandCardData.value_nPutCardList.push_back(tmp_2);
				clsHandCardData.value_nPutCardList.push_back(tmp_3);
				clsHandCardData.value_nPutCardList.push_back(tmp_3);
			}
			clsHandCardData.uctPutCardType = BestCardGroup;
			return;
		}
		

	//��֮����ǰ��ֵ��͵��ƣ����ڲ����ٿ��������ƿ��ܱ����ƴ��������
	for (int i = 3; i < 16; i++) 
	{
		if (clsHandCardData.value_aHandCardList[i] != 0&& clsHandCardData.value_aHandCardList[i] != 4)
		{
			//������
			if (clsHandCardData.value_aHandCardList[i] > 0)
			{
				clsHandCardData.value_aHandCardList[i]--;
				clsHandCardData.nHandCardCount--;
				HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
				clsHandCardData.value_aHandCardList[i]++;
				clsHandCardData.nHandCardCount++;
				if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
				{
					BestHandCardValue = tmpHandCardValue;
					BestCardGroup= get_GroupData(cgSINGLE, i, 1);
				}
			}
			//������
			if (clsHandCardData.value_aHandCardList[i] > 1)
			{
				//���Դ��һ���ƣ�����ʣ�����Ƽ�ֵ
				clsHandCardData.value_aHandCardList[i] -= 2;
				clsHandCardData.nHandCardCount -= 2;
				HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
				clsHandCardData.value_aHandCardList[i] += 2;
				clsHandCardData.nHandCardCount += 2;

				//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
				if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
				{
					BestHandCardValue = tmpHandCardValue;
					BestCardGroup = get_GroupData(cgDOUBLE, i, 2);
				}
			}
			//������
			if (clsHandCardData.value_aHandCardList[i] > 2)
			{
				clsHandCardData.value_aHandCardList[i] -= 3;
				clsHandCardData.nHandCardCount -= 3;
				HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
				clsHandCardData.value_aHandCardList[i] += 3;
				clsHandCardData.nHandCardCount += 3;

				//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
				if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
				{
					BestHandCardValue = tmpHandCardValue;
					BestCardGroup = get_GroupData(cgTHREE, i, 3);
				}
			}
			//����˳
			if (clsHandCardData.value_aHandCardList[i] > 0)
			{
				int prov = 0;
				for (int j = i; j < 15; j++)
				{
					if(clsHandCardData.value_aHandCardList[j]>0)
					{
						prov++;
					}
					else
					{
						break;
					}
					if (prov >= 5)
					{

						for (int k = i; k <= j; k++)
						{
							clsHandCardData.value_aHandCardList[k] --;
						}
						clsHandCardData.nHandCardCount -= prov;
						HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
						for (int k = i; k <= j; k++)
						{
							clsHandCardData.value_aHandCardList[k] ++;
						}
						clsHandCardData.nHandCardCount += prov;

						//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
						if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
						{
							BestHandCardValue = tmpHandCardValue;
							BestCardGroup = get_GroupData(cgSINGLE_LINE, j, prov);
						}
					}
				}
				
			}
			//��˫˳
			if (clsHandCardData.value_aHandCardList[i] > 1)
			{
				int prov = 0;
				for (int j = i; j < 15; j++)
				{
					if (clsHandCardData.value_aHandCardList[j]>1)
					{
						prov++;
					}
					else
					{
						break;
					}
					if (prov >= 3)
					{

						for (int k = i; k <= j; k++)
						{
							clsHandCardData.value_aHandCardList[k] -=2;
						}
						clsHandCardData.nHandCardCount -= prov*2;
						HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
						for (int k = i; k <= j; k++)
						{
							clsHandCardData.value_aHandCardList[k] +=2;
						}
						clsHandCardData.nHandCardCount += prov*2;

						//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
						if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
						{
							BestHandCardValue = tmpHandCardValue;
							BestCardGroup = get_GroupData(cgDOUBLE_LINE, j, prov*2);
						}
					}
				}
			}
			//����˳
			if(clsHandCardData.value_aHandCardList[i] > 2)
			{
				int prov = 0;
				for (int j = i; j < 15; j++)
				{
					if (clsHandCardData.value_aHandCardList[j]>2)
					{
						prov++;
					}
					else
					{
						break;
					}
					if (prov >= 2)
					{

						for (int k = i; k <= j; k++)
						{
							clsHandCardData.value_aHandCardList[k] -= 3;
						}
						clsHandCardData.nHandCardCount -= prov * 3;
						HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
						for (int k = i; k <= j; k++)
						{
							clsHandCardData.value_aHandCardList[k] += 3;
						}
						clsHandCardData.nHandCardCount += prov * 3;

						//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
						if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
						{
							BestHandCardValue = tmpHandCardValue;
							BestCardGroup = get_GroupData(cgTHREE_LINE, j, prov * 3);
						}
					}
				}
			}

			//����if������Ϊ����ʱi��ֵ��ô����Ҫ����һ�����

			if (BestCardGroup.cgType == cgERROR)
			{

			}
			else if (BestCardGroup.cgType == cgSINGLE)
			{
				clsHandCardData.value_nPutCardList.push_back(BestCardGroup.nMaxCard);
				clsHandCardData.uctPutCardType = BestCardGroup;
			}
			else if (BestCardGroup.cgType == cgDOUBLE)
			{
				clsHandCardData.value_nPutCardList.push_back(BestCardGroup.nMaxCard);
				clsHandCardData.value_nPutCardList.push_back(BestCardGroup.nMaxCard);
				clsHandCardData.uctPutCardType = BestCardGroup;
			}
			else if (BestCardGroup.cgType == cgTHREE)
			{
				clsHandCardData.value_nPutCardList.push_back(BestCardGroup.nMaxCard);
				clsHandCardData.value_nPutCardList.push_back(BestCardGroup.nMaxCard);
				clsHandCardData.value_nPutCardList.push_back(BestCardGroup.nMaxCard);
				clsHandCardData.uctPutCardType = BestCardGroup;
			}
			else if (BestCardGroup.cgType == cgSINGLE_LINE)
			{
				for (int j = BestCardGroup.nMaxCard- BestCardGroup.nCount+1; j <= BestCardGroup.nMaxCard; j++)
				{
					clsHandCardData.value_nPutCardList.push_back(j);
				}
				clsHandCardData.uctPutCardType = BestCardGroup;
			}
			else if (BestCardGroup.cgType == cgDOUBLE_LINE)
			{
				for (int j = BestCardGroup.nMaxCard - (BestCardGroup.nCount/2) + 1; j <= BestCardGroup.nMaxCard; j++)
				{
					clsHandCardData.value_nPutCardList.push_back(j);
					clsHandCardData.value_nPutCardList.push_back(j);
				}
				clsHandCardData.uctPutCardType = BestCardGroup;
			}
			else if (BestCardGroup.cgType == cgTHREE_LINE)
			{
				for (int j = BestCardGroup.nMaxCard - (BestCardGroup.nCount / 3) + 1; j <= BestCardGroup.nMaxCard; j++)
				{
					clsHandCardData.value_nPutCardList.push_back(j);
					clsHandCardData.value_nPutCardList.push_back(j);
					clsHandCardData.value_nPutCardList.push_back(j);
				}
				clsHandCardData.uctPutCardType = BestCardGroup;
			}
			else if (BestCardGroup.cgType == cgTHREE_TAKE_ONE)
			{
				clsHandCardData.value_nPutCardList.push_back(BestCardGroup.nMaxCard);
				clsHandCardData.value_nPutCardList.push_back(BestCardGroup.nMaxCard);
				clsHandCardData.value_nPutCardList.push_back(BestCardGroup.nMaxCard);
				clsHandCardData.value_nPutCardList.push_back(tmp_1);
				clsHandCardData.uctPutCardType = BestCardGroup;
			}
			else if (BestCardGroup.cgType == cgTHREE_TAKE_TWO)
			{
				clsHandCardData.value_nPutCardList.push_back(BestCardGroup.nMaxCard);
				clsHandCardData.value_nPutCardList.push_back(BestCardGroup.nMaxCard);
				clsHandCardData.value_nPutCardList.push_back(BestCardGroup.nMaxCard);
				clsHandCardData.value_nPutCardList.push_back(tmp_1);
				clsHandCardData.value_nPutCardList.push_back(tmp_1);
				clsHandCardData.uctPutCardType = BestCardGroup;
			}
			else if (BestCardGroup.cgType == cgTHREE_TAKE_ONE_LINE)
			{
				for (int j = BestCardGroup.nMaxCard - (BestCardGroup.nCount / 4) + 1; j <= BestCardGroup.nMaxCard; j++)
				{
					clsHandCardData.value_nPutCardList.push_back(j);
					clsHandCardData.value_nPutCardList.push_back(j);
					clsHandCardData.value_nPutCardList.push_back(j);
				}

				if (BestCardGroup.nCount / 4 == 2)
				{
					clsHandCardData.value_nPutCardList.push_back(tmp_1);
					clsHandCardData.value_nPutCardList.push_back(tmp_2);
				}
				if (BestCardGroup.nCount / 4 == 3)
				{
					clsHandCardData.value_nPutCardList.push_back(tmp_1);
					clsHandCardData.value_nPutCardList.push_back(tmp_2);
					clsHandCardData.value_nPutCardList.push_back(tmp_3);
				}
				if (BestCardGroup.nCount / 4 == 4)
				{
					clsHandCardData.value_nPutCardList.push_back(tmp_1);
					clsHandCardData.value_nPutCardList.push_back(tmp_2);
					clsHandCardData.value_nPutCardList.push_back(tmp_3);
					clsHandCardData.value_nPutCardList.push_back(tmp_4);
				}

				clsHandCardData.uctPutCardType = BestCardGroup;
			}
			else if (BestCardGroup.cgType == cgTHREE_TAKE_TWO_LINE)
			{
				for (int j = BestCardGroup.nMaxCard - (BestCardGroup.nCount / 5) + 1; j <= BestCardGroup.nMaxCard; j++)
				{
					clsHandCardData.value_nPutCardList.push_back(j);
					clsHandCardData.value_nPutCardList.push_back(j);
					clsHandCardData.value_nPutCardList.push_back(j);
				}
				if (BestCardGroup.nCount / 5 == 2)
				{
					clsHandCardData.value_nPutCardList.push_back(tmp_1);
					clsHandCardData.value_nPutCardList.push_back(tmp_1);
					clsHandCardData.value_nPutCardList.push_back(tmp_2);
					clsHandCardData.value_nPutCardList.push_back(tmp_2);
				}
				if (BestCardGroup.nCount / 5 == 3)
				{
					clsHandCardData.value_nPutCardList.push_back(tmp_1);
					clsHandCardData.value_nPutCardList.push_back(tmp_1);
					clsHandCardData.value_nPutCardList.push_back(tmp_2);
					clsHandCardData.value_nPutCardList.push_back(tmp_2);
					clsHandCardData.value_nPutCardList.push_back(tmp_3);
					clsHandCardData.value_nPutCardList.push_back(tmp_3);
				}
				clsHandCardData.uctPutCardType = BestCardGroup;
			}
			return;
		}
	}
	//���û��3-2�ķ�ը�ƣ��򿴿���û�е���
	if (clsHandCardData.value_aHandCardList[16] == 1 && clsHandCardData.value_aHandCardList[17] == 0)
	{
		clsHandCardData.value_nPutCardList.push_back(16);
		clsHandCardData.uctPutCardType = get_GroupData(cgSINGLE, 16, 1);
		return;
    }
	if (clsHandCardData.value_aHandCardList[16] == 0 && clsHandCardData.value_aHandCardList[17] == 1)
	{
		clsHandCardData.value_nPutCardList.push_back(17);
		clsHandCardData.uctPutCardType = get_GroupData(cgSINGLE, 17, 1);
		return;
	}
	//����Ҳû�У���ը��
	for (int i = 3; i < 16; i++)
	{
		if (clsHandCardData.value_aHandCardList[i] == 4)
		{
			clsHandCardData.value_nPutCardList.push_back(i);
			clsHandCardData.value_nPutCardList.push_back(i);
			clsHandCardData.value_nPutCardList.push_back(i);
			clsHandCardData.value_nPutCardList.push_back(i);

			clsHandCardData.uctPutCardType = get_GroupData(cgBOMB_CARD, i, 4);

			return;
		}
	}
	
	//�쳣����
	clsHandCardData.uctPutCardType = get_GroupData(cgERROR, 0, 0);
	return;

}

/*
2.0�汾����  ���ݳ������ƾ�����ǰԤ��������ơ�����֧����
*/
void get_PutCardList_2(GameSituation &clsGameSituation, HandCardData &clsHandCardData)
{
	if (clsGameSituation.nCardDroit == clsHandCardData.nOwnIndex)
	{
		get_PutCardList_2_unlimit(clsGameSituation, clsHandCardData);
	}
	else
	{
		get_PutCardList_2_limit(clsGameSituation, clsHandCardData);
	}
	return;
}


/*
2.0�汾����  ���ݳ������ƾ�����ǰԤ��������ơ�����������
*/
void get_PutCardList_2_limit(GameSituation &clsGameSituation, HandCardData &clsHandCardData)
{
	clsHandCardData.ClearPutCardList();


	/*��ը������ǰ����ֻ������ը��Ϊ�����ڶ��ֵ����ȳ����߼��������汾���ڴ˻������Ż�*/
	if (clsHandCardData.value_aHandCardList[17] > 0 && clsHandCardData.value_aHandCardList[16] > 0)
	{

		clsHandCardData.value_aHandCardList[17] --;
		clsHandCardData.value_aHandCardList[16] --;
		clsHandCardData.nHandCardCount -= 2;
		HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
		clsHandCardData.value_aHandCardList[16] ++;
		clsHandCardData.value_aHandCardList[17] ++;
		clsHandCardData.nHandCardCount += 2;
		if (tmpHandCardValue.NeedRound == 1)
		{
			clsHandCardData.value_nPutCardList.push_back(17);
			clsHandCardData.value_nPutCardList.push_back(16);
			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgKING_CARD, 17, 2);
			return;
		}
	}


	//��������  ����
	if (clsGameSituation.uctNowCardGroup.cgType == cgERROR)
	{
		clsHandCardData.uctPutCardType = get_GroupData(cgERROR, 0, 0);
		return;
	}
	//�������ͣ��ڱ������Ʋ�����Ҳ�Ǵ������� ����
	else if (clsGameSituation.uctNowCardGroup.cgType == cgZERO)
	{
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//��������
	else if (clsGameSituation.uctNowCardGroup.cgType == cgSINGLE)
	{

		//��֦������ܳ�ȥ���һ����ֱ�ӳ�
		CardGroupData SurCardGroupData = ins_SurCardsType(clsHandCardData.value_aHandCardList);
		if (SurCardGroupData.cgType != cgERROR)
		{
			if (SurCardGroupData.cgType == cgSINGLE&&SurCardGroupData.nMaxCard>clsGameSituation.uctNowCardGroup.nMaxCard)
			{
				Put_All_SurCards(clsGameSituation, clsHandCardData, SurCardGroupData);
				return;
			}
			else if (SurCardGroupData.cgType == cgBOMB_CARD|| SurCardGroupData.cgType == cgKING_CARD)
			{
				Put_All_SurCards(clsGameSituation, clsHandCardData, SurCardGroupData);
				return;
			}
		}     


		//�ݴ���ѵļ�ֵ
		HandCardValue BestHandCardValue = get_HandCardValue(clsHandCardData);


		//������Ϊ�����ƵĻ����ö���һ���ִΣ�����һ�֣�Ȩֵ����7�����ں����ĶԱȲο���
		BestHandCardValue.NeedRound += 1;

		//�ݴ���ѵ��ƺ�
		int BestMaxCard=0;
		//�Ƿ���Ƶı�־
		bool PutCards = false;


		for (int i = clsGameSituation.uctNowCardGroup.nMaxCard + 1; i < 18; i++)
		{
			if (clsHandCardData.value_aHandCardList[i] > 0)
			{
				//���Դ��һ���ƣ�����ʣ�����Ƽ�ֵ
				clsHandCardData.value_aHandCardList[i]--;
				clsHandCardData.nHandCardCount--;
				HandCardValue tmpHandCardValue=get_HandCardValue(clsHandCardData);
				clsHandCardData.value_aHandCardList[i]++;
				clsHandCardData.nHandCardCount++;

				//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
				if ((BestHandCardValue.SumValue-(BestHandCardValue.NeedRound*7)) <= (tmpHandCardValue.SumValue-(tmpHandCardValue.NeedRound*7)))
				{
					BestHandCardValue = tmpHandCardValue;
					BestMaxCard = i;
					PutCards = true;
				}

			}
		}
		if (PutCards)
		{
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgSINGLE, BestMaxCard, 1);
			return;
		}

		//-------------------------------------------ը��-------------------------------------------

		for (int i = 3; i < 16; i++)
		{
			if (clsHandCardData.value_aHandCardList[i] == 4)
			{

				//���Դ��ը��������ʣ�����Ƽ�ֵ,��Ϊը�����Բ���˳�ӣ�������ΪӰ��˳�Ӷ������ը
				clsHandCardData.value_aHandCardList[i] -= 4;
				clsHandCardData.nHandCardCount -= 4;
				HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
				clsHandCardData.value_aHandCardList[i] += 4;
				clsHandCardData.nHandCardCount += 4;

				//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
				if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7))
					//���ʣ�����Ƽ�ֵΪ����֤����ȥ�ļ��ʺܴ� ��ô������ը�������
					|| tmpHandCardValue.SumValue > 0)
				{
					BestHandCardValue = tmpHandCardValue;
					BestMaxCard = i;
					PutCards = true;
				}

			}
		}
		if (PutCards)
		{
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgBOMB_CARD, BestMaxCard, 4);
			return;
		}

		//��ը
		if (clsHandCardData.value_aHandCardList[17] > 0 && clsHandCardData.value_aHandCardList[16] > 0)
		{
			//���ʣ�����Ƽ�ֵΪ����֤����ȥ�ļ��ʺܴ���ô������ը������֣���ը20��
			if (BestHandCardValue.SumValue > 20)
			{
				clsHandCardData.value_nPutCardList.push_back(17);
				clsHandCardData.value_nPutCardList.push_back(16);
				clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgKING_CARD, 17, 2);
				return;
			}
		}


		
	    //�ܲ���
	    clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
		

	}
	//��������
	else if (clsGameSituation.uctNowCardGroup.cgType == cgDOUBLE)
	{
		//��֦������ܳ�ȥ���һ����ֱ�ӳ�
		CardGroupData SurCardGroupData = ins_SurCardsType(clsHandCardData.value_aHandCardList);
		if (SurCardGroupData.cgType != cgERROR)
		{
			if (SurCardGroupData.cgType == cgDOUBLE&&SurCardGroupData.nMaxCard>clsGameSituation.uctNowCardGroup.nMaxCard)
			{
				Put_All_SurCards(clsGameSituation, clsHandCardData, SurCardGroupData);
				return;
			}
			else if (SurCardGroupData.cgType == cgBOMB_CARD || SurCardGroupData.cgType == cgKING_CARD)
			{
				Put_All_SurCards(clsGameSituation, clsHandCardData, SurCardGroupData);
				return;
			}
		}
		//-------------------------------------------����-------------------------------------------

		//�ݴ���ѵļ�ֵ
		HandCardValue BestHandCardValue = get_HandCardValue(clsHandCardData);

		//������Ϊ�����ƵĻ����ö���һ���ִΣ�����һ�֣�Ȩֵ����7�����ں����ĶԱȲο���
		BestHandCardValue.NeedRound += 1;

		//�ݴ���ѵ��ƺ�
		int BestMaxCard = 0;
		//�Ƿ���Ƶı�־
		bool PutCards = false;

		for (int i = clsGameSituation.uctNowCardGroup.nMaxCard + 1; i < 18; i++)
		{
			if (clsHandCardData.value_aHandCardList[i] > 1)
			{
				//���Դ��һ���ƣ�����ʣ�����Ƽ�ֵ
				clsHandCardData.value_aHandCardList[i]-=2;
				clsHandCardData.nHandCardCount-=2;
				HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
				clsHandCardData.value_aHandCardList[i]+=2;
				clsHandCardData.nHandCardCount+=2;

				//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
				if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
				{
					BestHandCardValue = tmpHandCardValue;
					BestMaxCard = i;
					PutCards = true;
				}

			}
		}
		if (PutCards)
		{
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgDOUBLE, BestMaxCard, 2);
			return;
		}


		//-------------------------------------------ը��-------------------------------------------

		for (int i = 3; i < 16; i++)
		{
			if (clsHandCardData.value_aHandCardList[i] ==4)
			{

				//���Դ��ը��������ʣ�����Ƽ�ֵ,��Ϊը�����Բ���˳�ӣ�������ΪӰ��˳�Ӷ������ը
				clsHandCardData.value_aHandCardList[i] -= 4;
				clsHandCardData.nHandCardCount -= 4;
				HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
				clsHandCardData.value_aHandCardList[i] += 4;
				clsHandCardData.nHandCardCount += 4;

				//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
				if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7))
				//���ʣ�����Ƽ�ֵΪ����֤����ȥ�ļ��ʺܴ� ��ô������ը�������
					|| tmpHandCardValue.SumValue > 0)
				{
					BestHandCardValue = tmpHandCardValue;
					BestMaxCard = i;
					PutCards = true;
				}

			}
		}
		if (PutCards)
		{
		    clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgBOMB_CARD, BestMaxCard, 4);
			return;
		}

		//��ը
		if (clsHandCardData.value_aHandCardList[17] > 0 && clsHandCardData.value_aHandCardList[16] > 0)
		{
			//���ʣ�����Ƽ�ֵΪ����֤����ȥ�ļ��ʺܴ���ô������ը������֣���ը20��
			if (BestHandCardValue.SumValue > 20)
			{
				clsHandCardData.value_nPutCardList.push_back(17);
				clsHandCardData.value_nPutCardList.push_back(16);
				clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgKING_CARD, 17, 2);
				return;
			}
		}

		//�ܲ���
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//��������
	else if (clsGameSituation.uctNowCardGroup.cgType == cgTHREE)
	{
		//��֦������ܳ�ȥ���һ����ֱ�ӳ�
		CardGroupData SurCardGroupData = ins_SurCardsType(clsHandCardData.value_aHandCardList);
		if (SurCardGroupData.cgType != cgERROR)
		{
			if (SurCardGroupData.cgType == cgTHREE&&SurCardGroupData.nMaxCard>clsGameSituation.uctNowCardGroup.nMaxCard)
			{
				Put_All_SurCards(clsGameSituation, clsHandCardData, SurCardGroupData);
				return;
			}
			else if (SurCardGroupData.cgType == cgBOMB_CARD || SurCardGroupData.cgType == cgKING_CARD)
			{
				Put_All_SurCards(clsGameSituation, clsHandCardData, SurCardGroupData);
				return;
			}
		}
		//-------------------------------------------����-------------------------------------------

		//�ݴ���ѵļ�ֵ
		HandCardValue BestHandCardValue = get_HandCardValue(clsHandCardData);


		//������Ϊ�����ƵĻ����ö���һ���ִΣ�����һ�֣�Ȩֵ����7�����ں����ĶԱȲο���
		BestHandCardValue.NeedRound += 1;

		//�ݴ���ѵ��ƺ�
		int BestMaxCard = 0;
		//�Ƿ���Ƶı�־
		bool PutCards = false;

		for (int i = clsGameSituation.uctNowCardGroup.nMaxCard + 1; i < 18; i++)
		{
			if (clsHandCardData.value_aHandCardList[i] > 2)
			{
				//���Դ��һ���ƣ�����ʣ�����Ƽ�ֵ
				clsHandCardData.value_aHandCardList[i] -= 3;
				clsHandCardData.nHandCardCount -= 3;
				HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
				clsHandCardData.value_aHandCardList[i] += 3;
				clsHandCardData.nHandCardCount += 3;

				//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
				if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
				{
					BestHandCardValue = tmpHandCardValue;
					BestMaxCard = i;
					PutCards = true;
				}

			}
		}
		if (PutCards)
		{
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgTHREE, BestMaxCard, 3);
			return;
		}


		//-------------------------------------------ը��-------------------------------------------

		for (int i = 3; i < 16; i++)
		{
			if (clsHandCardData.value_aHandCardList[i] == 4)
			{

				//���Դ��ը��������ʣ�����Ƽ�ֵ,��Ϊը�����Բ���˳�ӣ�������ΪӰ��˳�Ӷ������ը
				clsHandCardData.value_aHandCardList[i] -= 4;
				clsHandCardData.nHandCardCount -= 4;
				HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
				clsHandCardData.value_aHandCardList[i] += 4;
				clsHandCardData.nHandCardCount += 4;

				//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
				if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7))
					//���ʣ�����Ƽ�ֵΪ����֤����ȥ�ļ��ʺܴ� ��ô������ը�������
					|| tmpHandCardValue.SumValue > 0)
				{
					BestHandCardValue = tmpHandCardValue;
					BestMaxCard = i;
					PutCards = true;
				}

			}
		}
		if (PutCards)
		{
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgBOMB_CARD, BestMaxCard, 4);
			return;
		}

		//��ը
		if (clsHandCardData.value_aHandCardList[17] > 0 && clsHandCardData.value_aHandCardList[16] > 0)
		{
			//���ʣ�����Ƽ�ֵΪ����֤����ȥ�ļ��ʺܴ���ô������ը������֣���ը20��
			if (BestHandCardValue.SumValue > 20)
			{
				clsHandCardData.value_nPutCardList.push_back(17);
				clsHandCardData.value_nPutCardList.push_back(16);
				clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgKING_CARD, 17, 2);
				return;
			}
		}

		//�ܲ���
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//��������
	else if (clsGameSituation.uctNowCardGroup.cgType == cgSINGLE_LINE)
	{
		//��֦������ܳ�ȥ���һ����ֱ�ӳ�
		CardGroupData SurCardGroupData = ins_SurCardsType(clsHandCardData.value_aHandCardList);
		if (SurCardGroupData.cgType != cgERROR)
		{
			if (SurCardGroupData.cgType == cgSINGLE_LINE&&SurCardGroupData.nMaxCard>clsGameSituation.uctNowCardGroup.nMaxCard
				&&SurCardGroupData.nCount== clsGameSituation.uctNowCardGroup.nCount)
			{
				Put_All_SurCards(clsGameSituation, clsHandCardData, SurCardGroupData);
				return;
			}
			else if (SurCardGroupData.cgType == cgBOMB_CARD || SurCardGroupData.cgType == cgKING_CARD)
			{
				Put_All_SurCards(clsGameSituation, clsHandCardData, SurCardGroupData);
				return;
			}
		}


		//�ݴ���ѵļ�ֵ
		HandCardValue BestHandCardValue = get_HandCardValue(clsHandCardData);


		//������Ϊ�����ƵĻ����ö���һ���ִΣ�����һ�֣�Ȩֵ����7�����ں����ĶԱȲο���
		BestHandCardValue.NeedRound += 1;

		//�ݴ���ѵ��ƺ�
		int BestMaxCard = 0;
		//�Ƿ���Ƶı�־
		bool PutCards = false;
		//��֤˳�ӵı�־
		int prov = 0;
		//˳�����
		int start_i = 0;
		//˳���յ�
		int end_i = 0;
		//˳�ӳ���
		int length = clsGameSituation.uctNowCardGroup.nCount;
		//2����������˳�ӣ��ӵ�ǰ�Ѵ����˳����С��ֵ+1��ʼ����
		for (int i = clsGameSituation.uctNowCardGroup.nMaxCard - length + 2; i < 15; i++)
		{
			/*
			����һ�������ε����⣬�������ĳ���Ƹ���Ϊ0����ô��Ȼ�����ھ�������˳��
			��ô�ͰѼ��������㣬������������ȴ��ڵ���˳�ӳ��ȣ����������˳�ӣ������Ե�ǰ�±�iΪ��߱�־
			�ٸ����ӣ��Է�����Ϊ34567���Ҵ�4������8�������㣬��ʱend_i=8����45678�������ߵ�9���������㣬end_i=9
			��56789����û��10����prov���㣬��һ��ѭ����11���ڣ���prov=1��
			*/
			if (clsHandCardData.value_aHandCardList[i] > 0)
			{
				prov++;
			}
			else
			{
				prov = 0;
			}
			if (prov >= length)
			{
				end_i = i;
				start_i = i - length + 1;

				for (int j = start_i; j <= end_i; j++)
				{
					clsHandCardData.value_aHandCardList[j] --;
				}
				clsHandCardData.nHandCardCount -= clsGameSituation.uctNowCardGroup.nCount;
				HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
				for (int j = start_i; j <= end_i; j++)
				{
					clsHandCardData.value_aHandCardList[j] ++;
				}
				clsHandCardData.nHandCardCount += clsGameSituation.uctNowCardGroup.nCount;

				//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
				if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
				{
					BestHandCardValue = tmpHandCardValue;
					BestMaxCard = end_i;
					PutCards = true;
				}

			}
		}
			
		if (PutCards)
		{
			for (int j = start_i; j <= end_i; j++)
			{
				clsHandCardData.value_nPutCardList.push_back(j);
			}		
			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgSINGLE_LINE, BestMaxCard, clsGameSituation.uctNowCardGroup.nCount);
			return;
		}

		//-------------------------------------------ը��-------------------------------------------

		for (int i = 3; i < 16; i++)
		{
			if (clsHandCardData.value_aHandCardList[i] == 4)
			{

				//���Դ��ը��������ʣ�����Ƽ�ֵ,��Ϊը�����Բ���˳�ӣ�������ΪӰ��˳�Ӷ������ը
				clsHandCardData.value_aHandCardList[i] -= 4;
				clsHandCardData.nHandCardCount -= 4;
				HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
				clsHandCardData.value_aHandCardList[i] += 4;
				clsHandCardData.nHandCardCount += 4;

				//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
				if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7))
					//���ʣ�����Ƽ�ֵΪ����֤����ȥ�ļ��ʺܴ� ��ô������ը�������
					|| tmpHandCardValue.SumValue > 0)
				{
					BestHandCardValue = tmpHandCardValue;
					BestMaxCard = i;
					PutCards = true;
				}

			}
		}
		if (PutCards)
		{
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgBOMB_CARD, BestMaxCard, 4);
			return;
		}

		//��ը
		if (clsHandCardData.value_aHandCardList[17] > 0 && clsHandCardData.value_aHandCardList[16] > 0)
		{
			//���ʣ�����Ƽ�ֵΪ����֤����ȥ�ļ��ʺܴ���ô������ը������֣���ը20��
			if (BestHandCardValue.SumValue > 20)
			{
				clsHandCardData.value_nPutCardList.push_back(17);
				clsHandCardData.value_nPutCardList.push_back(16);
				clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgKING_CARD, 17, 2);
				return;
			}
		}



		//�ܲ���
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//��������
	else if (clsGameSituation.uctNowCardGroup.cgType == cgDOUBLE_LINE)
	{
		//��֦������ܳ�ȥ���һ����ֱ�ӳ�
		CardGroupData SurCardGroupData = ins_SurCardsType(clsHandCardData.value_aHandCardList);
		if (SurCardGroupData.cgType != cgERROR)
		{
			if (SurCardGroupData.cgType == cgDOUBLE_LINE&&SurCardGroupData.nMaxCard>clsGameSituation.uctNowCardGroup.nMaxCard
				&&SurCardGroupData.nCount == clsGameSituation.uctNowCardGroup.nCount)
			{
				Put_All_SurCards(clsGameSituation, clsHandCardData, SurCardGroupData);
				return;
			}
			else if (SurCardGroupData.cgType == cgBOMB_CARD || SurCardGroupData.cgType == cgKING_CARD)
			{
				Put_All_SurCards(clsGameSituation, clsHandCardData, SurCardGroupData);
				return;
			}
		}


		//�ݴ���ѵļ�ֵ
		HandCardValue BestHandCardValue = get_HandCardValue(clsHandCardData);


		//������Ϊ�����ƵĻ����ö���һ���ִΣ�����һ�֣�Ȩֵ����7�����ں����ĶԱȲο���
		BestHandCardValue.NeedRound += 1;

		//�ݴ���ѵ��ƺ�
		int BestMaxCard = 0;
		//�Ƿ���Ƶı�־
		bool PutCards = false;
		//��֤˳�ӵı�־
		int prov = 0;
		//˳�����
		int start_i = 0;
		//˳���յ�
		int end_i = 0;
		//˳�ӳ���
		int length = clsGameSituation.uctNowCardGroup.nCount/2;
		//2����������˳�ӣ��ӵ�ǰ�Ѵ����˳����С��ֵ+1��ʼ����
		for (int i = clsGameSituation.uctNowCardGroup.nMaxCard - length + 2; i < 15; i++)
		{
			if (clsHandCardData.value_aHandCardList[i] > 1)
			{
				prov++;
			}
			else
			{
				prov = 0;
			}
			if (prov >= length)
			{
				end_i = i;
				start_i = i - length + 1;

				for (int j = start_i; j <= end_i; j++)
				{
					clsHandCardData.value_aHandCardList[j] -=2;
				}
				clsHandCardData.nHandCardCount -= clsGameSituation.uctNowCardGroup.nCount;
				HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
				for (int j = start_i; j <= end_i; j++)
				{
					clsHandCardData.value_aHandCardList[j] +=2;
				}
				clsHandCardData.nHandCardCount += clsGameSituation.uctNowCardGroup.nCount;

				//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
				if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
				{
					BestHandCardValue = tmpHandCardValue;
					BestMaxCard = end_i;
					PutCards = true;
				}

			}
		}

		if (PutCards)
		{
			for (int j = start_i; j <= end_i; j++)
			{
				clsHandCardData.value_nPutCardList.push_back(j);
				clsHandCardData.value_nPutCardList.push_back(j);
			}
			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgDOUBLE_LINE, BestMaxCard, clsGameSituation.uctNowCardGroup.nCount);
			return;
		}

		//-------------------------------------------ը��-------------------------------------------

		for (int i = 3; i < 16; i++)
		{
			if (clsHandCardData.value_aHandCardList[i] == 4)
			{

				//���Դ��ը��������ʣ�����Ƽ�ֵ,��Ϊը�����Բ���˳�ӣ�������ΪӰ��˳�Ӷ������ը
				clsHandCardData.value_aHandCardList[i] -= 4;
				clsHandCardData.nHandCardCount -= 4;
				HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
				clsHandCardData.value_aHandCardList[i] += 4;
				clsHandCardData.nHandCardCount += 4;

				//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
				if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7))
					//���ʣ�����Ƽ�ֵΪ����֤����ȥ�ļ��ʺܴ� ��ô������ը�������
					|| tmpHandCardValue.SumValue > 0)
				{
					BestHandCardValue = tmpHandCardValue;
					BestMaxCard = i;
					PutCards = true;
				}

			}
		}
		if (PutCards)
		{
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgBOMB_CARD, BestMaxCard, 4);
			return;
		}

		//��ը
		if (clsHandCardData.value_aHandCardList[17] > 0 && clsHandCardData.value_aHandCardList[16] > 0)
		{
			//���ʣ�����Ƽ�ֵΪ����֤����ȥ�ļ��ʺܴ���ô������ը������֣���ը20��
			if (BestHandCardValue.SumValue > 20)
			{
				clsHandCardData.value_nPutCardList.push_back(17);
				clsHandCardData.value_nPutCardList.push_back(16);
				clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgKING_CARD, 17, 2);
				return;
			}
		}



		//�ܲ���
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;

	}
	//��������
	else if (clsGameSituation.uctNowCardGroup.cgType == cgTHREE_LINE)
	{
		//��֦������ܳ�ȥ���һ����ֱ�ӳ�
		CardGroupData SurCardGroupData = ins_SurCardsType(clsHandCardData.value_aHandCardList);
		if (SurCardGroupData.cgType != cgERROR)
		{
			if (SurCardGroupData.cgType == cgTHREE_LINE&&SurCardGroupData.nMaxCard>clsGameSituation.uctNowCardGroup.nMaxCard
				&&SurCardGroupData.nCount == clsGameSituation.uctNowCardGroup.nCount)
			{
				Put_All_SurCards(clsGameSituation, clsHandCardData, SurCardGroupData);
				return;
			}
			else if (SurCardGroupData.cgType == cgBOMB_CARD || SurCardGroupData.cgType == cgKING_CARD)
			{
				Put_All_SurCards(clsGameSituation, clsHandCardData, SurCardGroupData);
				return;
			}
		}


		//�ݴ���ѵļ�ֵ
		HandCardValue BestHandCardValue = get_HandCardValue(clsHandCardData);


		//������Ϊ�����ƵĻ����ö���һ���ִΣ�����һ�֣�Ȩֵ����7�����ں����ĶԱȲο���
		BestHandCardValue.NeedRound += 1;

		//�ݴ���ѵ��ƺ�
		int BestMaxCard = 0;
		//�Ƿ���Ƶı�־
		bool PutCards = false;
		//��֤˳�ӵı�־
		int prov = 0;
		//˳�����
		int start_i = 0;
		//˳���յ�
		int end_i = 0;
		//˳�ӳ���
		int length = clsGameSituation.uctNowCardGroup.nCount / 3;
		//2����������˳�ӣ��ӵ�ǰ�Ѵ����˳����С��ֵ+1��ʼ����
		for (int i = clsGameSituation.uctNowCardGroup.nMaxCard - length + 2; i < 15; i++)
		{
			if (clsHandCardData.value_aHandCardList[i] > 2)
			{
				prov++;
			}
			else
			{
				prov = 0;
			}
			if (prov >= length)
			{
				end_i = i;
				start_i = i - length + 1;

				for (int j = start_i; j <= end_i; j++)
				{
					clsHandCardData.value_aHandCardList[j] -= 3;
				}
				clsHandCardData.nHandCardCount -= clsGameSituation.uctNowCardGroup.nCount;
				HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
				for (int j = start_i; j <= end_i; j++)
				{
					clsHandCardData.value_aHandCardList[j] += 3;
				}
				clsHandCardData.nHandCardCount += clsGameSituation.uctNowCardGroup.nCount;

				//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
				if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
				{
					BestHandCardValue = tmpHandCardValue;
					BestMaxCard = end_i;
					PutCards = true;
				}

			}
		}

		if (PutCards)
		{
			for (int j = start_i; j <= end_i; j++)
			{
				clsHandCardData.value_nPutCardList.push_back(j);
				clsHandCardData.value_nPutCardList.push_back(j);
				clsHandCardData.value_nPutCardList.push_back(j);
			}
			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgTHREE_LINE, BestMaxCard, clsGameSituation.uctNowCardGroup.nCount);
			return;
		}

		//-------------------------------------------ը��-------------------------------------------

		for (int i = 3; i < 16; i++)
		{
			if (clsHandCardData.value_aHandCardList[i] == 4)
			{

				//���Դ��ը��������ʣ�����Ƽ�ֵ,��Ϊը�����Բ���˳�ӣ�������ΪӰ��˳�Ӷ������ը
				clsHandCardData.value_aHandCardList[i] -= 4;
				clsHandCardData.nHandCardCount -= 4;
				HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
				clsHandCardData.value_aHandCardList[i] += 4;
				clsHandCardData.nHandCardCount += 4;

				//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
				if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7))
					//���ʣ�����Ƽ�ֵΪ����֤����ȥ�ļ��ʺܴ� ��ô������ը�������
					|| tmpHandCardValue.SumValue > 0)
				{
					BestHandCardValue = tmpHandCardValue;
					BestMaxCard = i;
					PutCards = true;
				}

			}
		}
		if (PutCards)
		{
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgBOMB_CARD, BestMaxCard, 4);
			return;
		}

		//��ը
		if (clsHandCardData.value_aHandCardList[17] > 0 && clsHandCardData.value_aHandCardList[16] > 0)
		{
			//���ʣ�����Ƽ�ֵΪ����֤����ȥ�ļ��ʺܴ���ô������ը������֣���ը20��
			if (BestHandCardValue.SumValue > 20)
			{
				clsHandCardData.value_nPutCardList.push_back(17);
				clsHandCardData.value_nPutCardList.push_back(16);
				clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgKING_CARD, 17, 2);
				return;
			}
		}



		//�ܲ���
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//����һ��
	else if (clsGameSituation.uctNowCardGroup.cgType == cgTHREE_TAKE_ONE)
	{
		//��֦������ܳ�ȥ���һ����ֱ�ӳ�
		CardGroupData SurCardGroupData = ins_SurCardsType(clsHandCardData.value_aHandCardList);
		if (SurCardGroupData.cgType != cgERROR)
		{
			if (SurCardGroupData.cgType == cgTHREE_TAKE_ONE&&SurCardGroupData.nMaxCard>clsGameSituation.uctNowCardGroup.nMaxCard)
			{
				Put_All_SurCards(clsGameSituation, clsHandCardData, SurCardGroupData);
				return;
			}
			else if (SurCardGroupData.cgType == cgBOMB_CARD || SurCardGroupData.cgType == cgKING_CARD)
			{
				Put_All_SurCards(clsGameSituation, clsHandCardData, SurCardGroupData);
				return;
			}
		}
	    		   
		//�ݴ���ѵļ�ֵ
		HandCardValue BestHandCardValue = get_HandCardValue(clsHandCardData);
		//������Ϊ�����ƵĻ����ö���һ���ִΣ�����һ�֣�Ȩֵ����7�����ں����ĶԱȲο���
		BestHandCardValue.NeedRound += 1;
		//�ݴ���ѵ��ƺ�
		int BestMaxCard = 0;
		//˳����ȥ����
		int tmp_1 = 0;
		//�Ƿ���Ƶı�־
		bool PutCards = false;
		//����һ
		for (int i = clsGameSituation.uctNowCardGroup.nMaxCard + 1; i < 16; i++)
		{
			if (clsHandCardData.value_aHandCardList[i] >2)
			{
				for (int j = 3; j < 18; j++)
				{
					//ѡ��һ�����ϵ����Ҳ���ѡ�����ŵ��Ǹ���
					if (clsHandCardData.value_aHandCardList[j] > 0 && j != i)
					{
						clsHandCardData.value_aHandCardList[i] -= 3;
						clsHandCardData.value_aHandCardList[j] -= 1;
						clsHandCardData.nHandCardCount -= 4;
						HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
						clsHandCardData.value_aHandCardList[i] += 3;
						clsHandCardData.value_aHandCardList[j] += 1;
						clsHandCardData.nHandCardCount += 4;
						//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
						if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
						{
							BestHandCardValue = tmpHandCardValue;
							BestMaxCard = i;
							tmp_1 = j;
							PutCards = true;
						}
					}
				}
			}
		}
		if (PutCards)
		{
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(tmp_1);
			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgTHREE_TAKE_ONE, BestMaxCard, 4);
			return;
		}
		//-------------------------------------------ը��-------------------------------------------

		for (int i = 3; i < 16; i++)
		{
			if (clsHandCardData.value_aHandCardList[i] == 4)
			{

				//���Դ��ը��������ʣ�����Ƽ�ֵ,��Ϊը�����Բ���˳�ӣ�������ΪӰ��˳�Ӷ������ը
				clsHandCardData.value_aHandCardList[i] -= 4;
				clsHandCardData.nHandCardCount -= 4;
				HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
				clsHandCardData.value_aHandCardList[i] += 4;
				clsHandCardData.nHandCardCount += 4;

				//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
				if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7))
					//���ʣ�����Ƽ�ֵΪ����֤����ȥ�ļ��ʺܴ� ��ô������ը�������
					|| tmpHandCardValue.SumValue > 0)
				{
					BestHandCardValue = tmpHandCardValue;
					BestMaxCard = i;
					PutCards = true;
				}

			}
		}
		if (PutCards)
		{
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgBOMB_CARD, BestMaxCard, 4);
			return;
		}

		//��ը
		if (clsHandCardData.value_aHandCardList[17] > 0 && clsHandCardData.value_aHandCardList[16] > 0)
		{
			//���ʣ�����Ƽ�ֵΪ����֤����ȥ�ļ��ʺܴ���ô������ը������֣���ը20��
			if (BestHandCardValue.SumValue > 20)
			{
				clsHandCardData.value_nPutCardList.push_back(17);
				clsHandCardData.value_nPutCardList.push_back(16);
				clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgKING_CARD, 17, 2);
				return;
			}
		}

		//�ܲ���
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//����һ��
	else if (clsGameSituation.uctNowCardGroup.cgType == cgTHREE_TAKE_TWO)
	{
		//��֦������ܳ�ȥ���һ����ֱ�ӳ�
		CardGroupData SurCardGroupData = ins_SurCardsType(clsHandCardData.value_aHandCardList);
		if (SurCardGroupData.cgType != cgERROR)
		{
			if (SurCardGroupData.cgType == cgTHREE_TAKE_TWO&&SurCardGroupData.nMaxCard>clsGameSituation.uctNowCardGroup.nMaxCard)
			{
				Put_All_SurCards(clsGameSituation, clsHandCardData, SurCardGroupData);
				return;
			}
			else if (SurCardGroupData.cgType == cgBOMB_CARD || SurCardGroupData.cgType == cgKING_CARD)
			{
				Put_All_SurCards(clsGameSituation, clsHandCardData, SurCardGroupData);
				return;
			}
		}

		//�ݴ���ѵļ�ֵ
		HandCardValue BestHandCardValue = get_HandCardValue(clsHandCardData);
		//������Ϊ�����ƵĻ����ö���һ���ִΣ�����һ�֣�Ȩֵ����7�����ں����ĶԱȲο���
		BestHandCardValue.NeedRound += 1;
		//�ݴ���ѵ��ƺ�
		int BestMaxCard = 0;
		//˳����ȥ����
		int tmp_1 = 0;
		//�Ƿ���Ƶı�־
		bool PutCards = false;
		//����һ
		for (int i = clsGameSituation.uctNowCardGroup.nMaxCard + 1; i < 16; i++)
		{
			if (clsHandCardData.value_aHandCardList[i] >2)
			{
				for (int j = 3; j < 16; j++)
				{
					//ѡ��һ�����ϵ����Ҳ���ѡ�����ŵ��Ǹ���
					if (clsHandCardData.value_aHandCardList[j] > 1 && j != i)
					{
						clsHandCardData.value_aHandCardList[i] -= 3;
						clsHandCardData.value_aHandCardList[j] -= 2;
						clsHandCardData.nHandCardCount -= 5;
						HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
						clsHandCardData.value_aHandCardList[i] += 3;
						clsHandCardData.value_aHandCardList[j] += 2;
						clsHandCardData.nHandCardCount += 5;
						//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
						if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
						{
							BestHandCardValue = tmpHandCardValue;
							BestMaxCard = i;
							tmp_1 = j;
							PutCards = true;
						}
					}
				}
			}
		}
		if (PutCards)
		{
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(tmp_1);
			clsHandCardData.value_nPutCardList.push_back(tmp_1);
			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgTHREE_TAKE_TWO, BestMaxCard, 5);
			return;
		}
		//-------------------------------------------ը��-------------------------------------------

		for (int i = 3; i < 16; i++)
		{
			if (clsHandCardData.value_aHandCardList[i] == 4)
			{

				//���Դ��ը��������ʣ�����Ƽ�ֵ,��Ϊը�����Բ���˳�ӣ�������ΪӰ��˳�Ӷ������ը
				clsHandCardData.value_aHandCardList[i] -= 4;
				clsHandCardData.nHandCardCount -= 4;
				HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
				clsHandCardData.value_aHandCardList[i] += 4;
				clsHandCardData.nHandCardCount += 4;

				//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
				if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7))
					//���ʣ�����Ƽ�ֵΪ����֤����ȥ�ļ��ʺܴ� ��ô������ը�������
					|| tmpHandCardValue.SumValue > 0)
				{
					BestHandCardValue = tmpHandCardValue;
					BestMaxCard = i;
					PutCards = true;
				}

			}
		}
		if (PutCards)
		{
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgBOMB_CARD, BestMaxCard, 4);
			return;
		}

		//��ը
		if (clsHandCardData.value_aHandCardList[17] > 0 && clsHandCardData.value_aHandCardList[16] > 0)
		{
			//���ʣ�����Ƽ�ֵΪ����֤����ȥ�ļ��ʺܴ���ô������ը������֣���ը20��
			if (BestHandCardValue.SumValue > 20)
			{
				clsHandCardData.value_nPutCardList.push_back(17);
				clsHandCardData.value_nPutCardList.push_back(16);
				clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgKING_CARD, 17, 2);
				return;
			}
		}

		//�ܲ���
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//����һ����
	else if (clsGameSituation.uctNowCardGroup.cgType == cgTHREE_TAKE_ONE_LINE)
	{
		//��֦������ܳ�ȥ���һ����ֱ�ӳ�
		CardGroupData SurCardGroupData = ins_SurCardsType(clsHandCardData.value_aHandCardList);
		if (SurCardGroupData.cgType != cgERROR)
		{
			if (SurCardGroupData.cgType == cgTHREE_TAKE_ONE_LINE&&SurCardGroupData.nMaxCard>clsGameSituation.uctNowCardGroup.nMaxCard
				&&SurCardGroupData.nCount == clsGameSituation.uctNowCardGroup.nCount)
			{
				Put_All_SurCards(clsGameSituation, clsHandCardData, SurCardGroupData);
				return;
			}
			else if (SurCardGroupData.cgType == cgBOMB_CARD || SurCardGroupData.cgType == cgKING_CARD)
			{
				Put_All_SurCards(clsGameSituation, clsHandCardData, SurCardGroupData);
				return;
			}
		}


		//�ݴ���ѵļ�ֵ
		HandCardValue BestHandCardValue = get_HandCardValue(clsHandCardData);


		//������Ϊ�����ƵĻ����ö���һ���ִΣ�����һ�֣�Ȩֵ����7�����ں����ĶԱȲο���
		BestHandCardValue.NeedRound += 1;

		//�ݴ���ѵ��ƺ�
		int BestMaxCard = 0;
		//�Ƿ���Ƶı�־
		bool PutCards = false;
		//��֤˳�ӵı�־
		int prov = 0;
		//˳�����
		int start_i = 0;
		//˳���յ�
		int end_i = 0;
		//˳�ӳ���
		int length = clsGameSituation.uctNowCardGroup.nCount / 4;

		int tmp_1 = 0;
		int tmp_2 = 0;
		int tmp_3 = 0;
		int tmp_4 = 0;
		//2����������˳�ӣ��ӵ�ǰ�Ѵ����˳����С��ֵ+1��ʼ����
		for (int i = clsGameSituation.uctNowCardGroup.nMaxCard - length + 2; i < 15; i++)
		{
			if (clsHandCardData.value_aHandCardList[i] > 2)
			{
				prov++;
			}
			else
			{
				prov = 0;
			}
			if (prov >= length)
			{
				end_i = i;
				start_i = i - length + 1;

				for (int j = start_i; j <= end_i; j++)
				{
					clsHandCardData.value_aHandCardList[j] -= 3;
				}			
				clsHandCardData.nHandCardCount -= clsGameSituation.uctNowCardGroup.nCount;

				/*��������ȫ����ѡȡ��������Ȼ��ö�ٳ���߼�ֵ�ģ������ǵ����ɻ�����Ҳ������2-4֮��
				���Ըɴ���������֧��������*/
				//Ϊ�����ɻ�
				if (length == 2)
				{
					for (int j = 3; j < 18; j++)
					{
						if (clsHandCardData.value_aHandCardList[j] > 0)
						{
							clsHandCardData.value_aHandCardList[j] -= 1;
							for (int k = 3; k < 18; k++)
							{
								if (clsHandCardData.value_aHandCardList[k] > 0)
								{
									clsHandCardData.value_aHandCardList[k] -= 1;
									HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
									clsHandCardData.value_aHandCardList[k] += 1;

									//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
									if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
									{
										BestHandCardValue = tmpHandCardValue;
										BestMaxCard = end_i;
										tmp_1 = j;
										tmp_2 = k;
										PutCards = true;
									}
								}
							}
							clsHandCardData.value_aHandCardList[j] += 1;
						}

					}
				}
				//Ϊ�����ɻ�
				if (length == 3)
				{
					for (int j = 3; j < 18; j++)
					{
						if (clsHandCardData.value_aHandCardList[j] > 0)
						{
							clsHandCardData.value_aHandCardList[j] -= 1;
							for (int k = 3; k < 18; k++)
							{
								if (clsHandCardData.value_aHandCardList[k] > 0)
								{
									clsHandCardData.value_aHandCardList[k] -= 1;
									for (int l = 3; l < 18; l++)
									{
										if (clsHandCardData.value_aHandCardList[l] > 0)
										{
											clsHandCardData.value_aHandCardList[l] -= 1;
											HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
											//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
											if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
											{
												BestHandCardValue = tmpHandCardValue;
												BestMaxCard = end_i;
												tmp_1 = j;
												tmp_2 = k;
												tmp_3 = l;
												PutCards = true;
											}
											clsHandCardData.value_aHandCardList[l] += 1;
										}
									}
									clsHandCardData.value_aHandCardList[k] += 1;
								}
							}
							clsHandCardData.value_aHandCardList[j] += 1;
						}
						

					}
				}
				//Ϊ�����ɻ�
				if (length == 4)
				{
					for (int j = 3; j < 18; j++)
					{
						if (clsHandCardData.value_aHandCardList[j] > 0)
						{
							clsHandCardData.value_aHandCardList[j] -= 1;
							for (int k = 3; k < 18; k++)
							{
								if (clsHandCardData.value_aHandCardList[k] > 0)
								{
									clsHandCardData.value_aHandCardList[k] -= 1;
									for (int l = 3; l < 18; l++)
									{
										if (clsHandCardData.value_aHandCardList[l] > 0)
										{
											clsHandCardData.value_aHandCardList[l] -= 1;
											for (int m = 3; m < 18; m++)
											{
												if (clsHandCardData.value_aHandCardList[m] > 0)
												{
													clsHandCardData.value_aHandCardList[m] -= 1;
													HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
													//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
													if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
													{
														BestHandCardValue = tmpHandCardValue;
														BestMaxCard = end_i;
														tmp_1 = j;
														tmp_2 = k;
														tmp_3 = l;
														tmp_4 = m;
														PutCards = true;
													}
													clsHandCardData.value_aHandCardList[m] += 1;
												}
											}
											clsHandCardData.value_aHandCardList[l] += 1;
										}
									}
									clsHandCardData.value_aHandCardList[k] += 1;
								}
							}
							clsHandCardData.value_aHandCardList[j] += 1;
						}


					}
				}
			
				for (int j = start_i; j <= end_i; j++)
				{
					clsHandCardData.value_aHandCardList[j] += 3;
				}
				clsHandCardData.nHandCardCount += clsGameSituation.uctNowCardGroup.nCount;
			}
		}

		if (PutCards)
		{
			for (int j = start_i; j <= end_i; j++)
			{
				clsHandCardData.value_nPutCardList.push_back(j);
				clsHandCardData.value_nPutCardList.push_back(j);
				clsHandCardData.value_nPutCardList.push_back(j);
			}

			if (length == 2)
			{
				clsHandCardData.value_nPutCardList.push_back(tmp_1);
				clsHandCardData.value_nPutCardList.push_back(tmp_2);
		    }
			if (length == 3)
			{
				clsHandCardData.value_nPutCardList.push_back(tmp_1);
				clsHandCardData.value_nPutCardList.push_back(tmp_2);
				clsHandCardData.value_nPutCardList.push_back(tmp_3);

			}
			if (length == 4)
			{
				clsHandCardData.value_nPutCardList.push_back(tmp_1);
				clsHandCardData.value_nPutCardList.push_back(tmp_2);
				clsHandCardData.value_nPutCardList.push_back(tmp_3);
				clsHandCardData.value_nPutCardList.push_back(tmp_4);
			}

			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgTHREE_TAKE_ONE_LINE, BestMaxCard, clsGameSituation.uctNowCardGroup.nCount);
			return;
		}

		//-------------------------------------------ը��-------------------------------------------

		for (int i = 3; i < 16; i++)
		{
			if (clsHandCardData.value_aHandCardList[i] == 4)
			{

				//���Դ��ը��������ʣ�����Ƽ�ֵ,��Ϊը�����Բ���˳�ӣ�������ΪӰ��˳�Ӷ������ը
				clsHandCardData.value_aHandCardList[i] -= 4;
				clsHandCardData.nHandCardCount -= 4;
				HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
				clsHandCardData.value_aHandCardList[i] += 4;
				clsHandCardData.nHandCardCount += 4;

				//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
				if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7))
					//���ʣ�����Ƽ�ֵΪ����֤����ȥ�ļ��ʺܴ� ��ô������ը�������
					|| tmpHandCardValue.SumValue > 0)
				{
					BestHandCardValue = tmpHandCardValue;
					BestMaxCard = i;
					PutCards = true;
				}

			}
		}
		if (PutCards)
		{
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgBOMB_CARD, BestMaxCard, 4);
			return;
		}

		//��ը
		if (clsHandCardData.value_aHandCardList[17] > 0 && clsHandCardData.value_aHandCardList[16] > 0)
		{
			//���ʣ�����Ƽ�ֵΪ����֤����ȥ�ļ��ʺܴ���ô������ը������֣���ը20��
			if (BestHandCardValue.SumValue > 20)
			{
				clsHandCardData.value_nPutCardList.push_back(17);
				clsHandCardData.value_nPutCardList.push_back(16);
				clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgKING_CARD, 17, 2);
				return;
			}
		}



		//�ܲ���
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//����һ����
	else if (clsGameSituation.uctNowCardGroup.cgType == cgTHREE_TAKE_TWO_LINE)
	{
		//��֦������ܳ�ȥ���һ����ֱ�ӳ�
		CardGroupData SurCardGroupData = ins_SurCardsType(clsHandCardData.value_aHandCardList);
		if (SurCardGroupData.cgType != cgERROR)
		{
			if (SurCardGroupData.cgType == cgTHREE_TAKE_TWO_LINE&&SurCardGroupData.nMaxCard>clsGameSituation.uctNowCardGroup.nMaxCard
				&&SurCardGroupData.nCount == clsGameSituation.uctNowCardGroup.nCount)
			{
				Put_All_SurCards(clsGameSituation, clsHandCardData, SurCardGroupData);
				return;
			}
			else if (SurCardGroupData.cgType == cgBOMB_CARD || SurCardGroupData.cgType == cgKING_CARD)
			{
				Put_All_SurCards(clsGameSituation, clsHandCardData, SurCardGroupData);
				return;
			}
		}


		//�ݴ���ѵļ�ֵ
		HandCardValue BestHandCardValue = get_HandCardValue(clsHandCardData);


		//������Ϊ�����ƵĻ����ö���һ���ִΣ�����һ�֣�Ȩֵ����7�����ں����ĶԱȲο���
		BestHandCardValue.NeedRound += 1;

		//�ݴ���ѵ��ƺ�
		int BestMaxCard = 0;
		//�Ƿ���Ƶı�־
		bool PutCards = false;
		//��֤˳�ӵı�־
		int prov = 0;
		//˳�����
		int start_i = 0;
		//˳���յ�
		int end_i = 0;
		//˳�ӳ���
		int length = clsGameSituation.uctNowCardGroup.nCount / 5;

		int tmp_1 = 0;
		int tmp_2 = 0;
		int tmp_3 = 0;
		//2����������˳�ӣ��ӵ�ǰ�Ѵ����˳����С��ֵ+1��ʼ����
		for (int i = clsGameSituation.uctNowCardGroup.nMaxCard - length + 2; i < 15; i++)
		{
			if (clsHandCardData.value_aHandCardList[i] > 2)
			{
				prov++;
			}
			else
			{
				prov = 0;
			}
			if (prov >= length)
			{
				end_i = i;
				start_i = i - length + 1;

				for (int j = start_i; j <= end_i; j++)
				{
					clsHandCardData.value_aHandCardList[j] -= 3;
				}
				clsHandCardData.nHandCardCount -= clsGameSituation.uctNowCardGroup.nCount;

				/*��������ȫ����ѡȡ��������Ȼ��ö�ٳ���߼�ֵ�ģ������ǵ����ɻ�����Ҳ������2-3֮��*/
				//Ϊ�����ɻ�
				if (length == 2)
				{
					for (int j = 3; j < 18; j++)
					{
						if (clsHandCardData.value_aHandCardList[j] > 1)
						{
							clsHandCardData.value_aHandCardList[j] -= 2;
							for (int k = 3; k < 18; k++)
							{
								if (clsHandCardData.value_aHandCardList[k] > 1)
								{
									clsHandCardData.value_aHandCardList[k] -= 2;
									HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
									clsHandCardData.value_aHandCardList[k] += 2;

									//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
									if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
									{
										BestHandCardValue = tmpHandCardValue;
										BestMaxCard = end_i;
										tmp_1 = j;
										tmp_2 = k;
										PutCards = true;
									}
								}
							}
							clsHandCardData.value_aHandCardList[j] += 2;
						}

					}
				}
				//Ϊ�����ɻ�
				if (length == 3)
				{
					for (int j = 3; j < 18; j++)
					{
						if (clsHandCardData.value_aHandCardList[j] > 1)
						{
							clsHandCardData.value_aHandCardList[j] -= 2;
							for (int k = 3; k < 18; k++)
							{
								if (clsHandCardData.value_aHandCardList[k] > 1)
								{
									clsHandCardData.value_aHandCardList[k] -= 2;
									for (int l = 3; l < 18; l++)
									{
										if (clsHandCardData.value_aHandCardList[l] > 1)
										{
											clsHandCardData.value_aHandCardList[l] -= 2;
											HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
											//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
											if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
											{
												BestHandCardValue = tmpHandCardValue;
												BestMaxCard = end_i;
												tmp_1 = j;
												tmp_2 = k;
												tmp_3 = l;
												PutCards = true;
											}
											clsHandCardData.value_aHandCardList[l] += 2;
										}
									}
									clsHandCardData.value_aHandCardList[k] += 2;
								}
							}
							clsHandCardData.value_aHandCardList[j] += 2;
						}


					}
				}

				for (int j = start_i; j <= end_i; j++)
				{
					clsHandCardData.value_aHandCardList[j] += 3;
				}
				clsHandCardData.nHandCardCount += clsGameSituation.uctNowCardGroup.nCount;
			}
		}

		if (PutCards)
		{
			for (int j = start_i; j <= end_i; j++)
			{
				clsHandCardData.value_nPutCardList.push_back(j);
				clsHandCardData.value_nPutCardList.push_back(j);
				clsHandCardData.value_nPutCardList.push_back(j);
			}

			if (length == 2)
			{
				clsHandCardData.value_nPutCardList.push_back(tmp_1);
				clsHandCardData.value_nPutCardList.push_back(tmp_1);
				clsHandCardData.value_nPutCardList.push_back(tmp_2);
				clsHandCardData.value_nPutCardList.push_back(tmp_2);
			}
			if (length == 3)
			{
				clsHandCardData.value_nPutCardList.push_back(tmp_1);
				clsHandCardData.value_nPutCardList.push_back(tmp_1);
				clsHandCardData.value_nPutCardList.push_back(tmp_2);
				clsHandCardData.value_nPutCardList.push_back(tmp_2);
				clsHandCardData.value_nPutCardList.push_back(tmp_3);
				clsHandCardData.value_nPutCardList.push_back(tmp_3);

			}

			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgTHREE_TAKE_ONE_LINE, BestMaxCard, clsGameSituation.uctNowCardGroup.nCount);
			return;
		}

		//-------------------------------------------ը��-------------------------------------------

		for (int i = 3; i < 16; i++)
		{
			if (clsHandCardData.value_aHandCardList[i] == 4)
			{

				//���Դ��ը��������ʣ�����Ƽ�ֵ,��Ϊը�����Բ���˳�ӣ�������ΪӰ��˳�Ӷ������ը
				clsHandCardData.value_aHandCardList[i] -= 4;
				clsHandCardData.nHandCardCount -= 4;
				HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
				clsHandCardData.value_aHandCardList[i] += 4;
				clsHandCardData.nHandCardCount += 4;

				//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
				if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7))
					//���ʣ�����Ƽ�ֵΪ����֤����ȥ�ļ��ʺܴ� ��ô������ը�������
					|| tmpHandCardValue.SumValue > 0)
				{
					BestHandCardValue = tmpHandCardValue;
					BestMaxCard = i;
					PutCards = true;
				}

			}
		}
		if (PutCards)
		{
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgBOMB_CARD, BestMaxCard, 4);
			return;
		}

		//��ը
		if (clsHandCardData.value_aHandCardList[17] > 0 && clsHandCardData.value_aHandCardList[16] > 0)
		{
			//���ʣ�����Ƽ�ֵΪ����֤����ȥ�ļ��ʺܴ���ô������ը������֣���ը20��
			if (BestHandCardValue.SumValue > 20)
			{
				clsHandCardData.value_nPutCardList.push_back(17);
				clsHandCardData.value_nPutCardList.push_back(16);
				clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgKING_CARD, 17, 2);
				return;
			}
		}



		//�ܲ���
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//�Ĵ�����
	else if (clsGameSituation.uctNowCardGroup.cgType == cgFOUR_TAKE_ONE)
	{
		//��֦������ܳ�ȥ���һ����ֱ�ӳ�
		CardGroupData SurCardGroupData = ins_SurCardsType(clsHandCardData.value_aHandCardList);
		if (SurCardGroupData.cgType != cgERROR)
		{
			if (SurCardGroupData.cgType == cgFOUR_TAKE_ONE&&SurCardGroupData.nMaxCard>clsGameSituation.uctNowCardGroup.nMaxCard)
			{
				Put_All_SurCards(clsGameSituation, clsHandCardData, SurCardGroupData);
				return;
			}
			else if (SurCardGroupData.cgType == cgBOMB_CARD || SurCardGroupData.cgType == cgKING_CARD)
			{
				Put_All_SurCards(clsGameSituation, clsHandCardData, SurCardGroupData);
				return;
			}
		}

		//�ݴ���ѵļ�ֵ
		HandCardValue BestHandCardValue = get_HandCardValue(clsHandCardData);
		/*������˵���������Զ�������������ը��ը���Ĵ������ը����˵�����������ƣ���������14Ȩֵ�ļ�ֵ
		����ǰ���Ƽ�ֵ����14������Ϊ������ը��ը�����ؿ����Ĵ��������棬������ô���ԡ�*/

		if (BestHandCardValue.SumValue > 14)
		{
			//ը����������ֱ��ը�������ǲ�ֺ������Ϊ������
			for (int i = 3; i < 16; i++)
			{
				if (clsHandCardData.value_aHandCardList[i] == 4)
				{
					clsHandCardData.value_nPutCardList.push_back(i);
					clsHandCardData.value_nPutCardList.push_back(i);
					clsHandCardData.value_nPutCardList.push_back(i);
					clsHandCardData.value_nPutCardList.push_back(i);

					clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgBOMB_CARD, i, 4);

					return;
				}
			}
			//��ը
			if (clsHandCardData.value_aHandCardList[17] > 0 && clsHandCardData.value_aHandCardList[16] > 0)
			{

				clsHandCardData.value_nPutCardList.push_back(17);
				clsHandCardData.value_nPutCardList.push_back(16);

				clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgKING_CARD, 17, 2);

				return;
			}
		}
		//������Ϊ�����ƵĻ����ö���һ���ִΣ�����һ�֣�Ȩֵ����7�����ں����ĶԱȲο���
		BestHandCardValue.NeedRound += 1;
		//�ݴ���ѵ��ƺ�
		int BestMaxCard = 0;
		//˳����ȥ����
		int tmp_1 = 0;
		int tmp_2 = 0;
		//�Ƿ���Ƶı�־
		bool PutCards = false;
		//ͬΪ�Ĵ���
		for (int i = clsGameSituation.uctNowCardGroup.nMaxCard + 1; i < 16; i++)
		{
			if (clsHandCardData.value_aHandCardList[i] == 4)
			{
				for (int j = 3; j < 18; j++)
				{
					//��ѡ��һ�����ϵ����Ҳ���ѡ�����ŵ��Ǹ���
					if (clsHandCardData.value_aHandCardList[j] > 0 && j != i)
					{
						//��ѡ��һ�����ϵ����Ҳ���ѡ�����ŵ��Ǹ����Ҳ��ǵ�һ��ѡ�������ڸ��ƣ��������Ĵ����������һ��,������ը��
						for (int k = j + 1; k < 18; k++)
						{
							if (clsHandCardData.value_aHandCardList[k] > 0 && k != i)
							{
								clsHandCardData.value_aHandCardList[i] -= 4;
								clsHandCardData.value_aHandCardList[j] -= 1;
								clsHandCardData.value_aHandCardList[k] -= 1;
								clsHandCardData.nHandCardCount -= 6;
								HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
								clsHandCardData.value_aHandCardList[i] += 4;
								clsHandCardData.value_aHandCardList[j] += 1;
								clsHandCardData.value_aHandCardList[k] += 1;
								clsHandCardData.nHandCardCount += 6;

								//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
								if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
								{
									BestHandCardValue = tmpHandCardValue;
									BestMaxCard = i;
									tmp_1 = j;
									tmp_2 = k;
									PutCards = true;
								}
							}
						}
					}
				}
			}
		}
		if (PutCards)
		{
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(tmp_1);
			clsHandCardData.value_nPutCardList.push_back(tmp_2);
			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgFOUR_TAKE_ONE, BestMaxCard, 6);
			return;
		}
		//����������Ȩֵ��С���������û��ѡ������õ��Ĵ������ͣ���ôҲҪը����Ϊ������
		for (int i = 3; i < 16; i++)
		{
			if (clsHandCardData.value_aHandCardList[i] == 4)
			{
				clsHandCardData.value_nPutCardList.push_back(i);
				clsHandCardData.value_nPutCardList.push_back(i);
				clsHandCardData.value_nPutCardList.push_back(i);
				clsHandCardData.value_nPutCardList.push_back(i);

				clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgBOMB_CARD, i, 4);

				return;
			}
		}
		//��ը
		if (clsHandCardData.value_aHandCardList[17] > 0 && clsHandCardData.value_aHandCardList[16] > 0)
		{

			clsHandCardData.value_nPutCardList.push_back(17);
			clsHandCardData.value_nPutCardList.push_back(16);

			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgKING_CARD, 17, 2);

			return;
		}
		//�ܲ���
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//�Ĵ�����
	else if (clsGameSituation.uctNowCardGroup.cgType == cgFOUR_TAKE_TWO)
	{
		//��֦������ܳ�ȥ���һ����ֱ�ӳ�
		CardGroupData SurCardGroupData = ins_SurCardsType(clsHandCardData.value_aHandCardList);
		if (SurCardGroupData.cgType != cgERROR)
		{
			if (SurCardGroupData.cgType == cgFOUR_TAKE_TWO&&SurCardGroupData.nMaxCard>clsGameSituation.uctNowCardGroup.nMaxCard)
			{
				Put_All_SurCards(clsGameSituation, clsHandCardData, SurCardGroupData);
				return;
			}
			else if (SurCardGroupData.cgType == cgBOMB_CARD || SurCardGroupData.cgType == cgKING_CARD)
			{
				Put_All_SurCards(clsGameSituation, clsHandCardData, SurCardGroupData);
				return;
			}
		}

		//�ݴ���ѵļ�ֵ
		HandCardValue BestHandCardValue = get_HandCardValue(clsHandCardData);
		/*������˵���������Զ�������������ը��ը���Ĵ������ը����˵�����������ƣ���������14Ȩֵ�ļ�ֵ
		����ǰ���Ƽ�ֵ����14������Ϊ������ը��ը�����ؿ����Ĵ��������棬������ô���ԡ�*/

		if (BestHandCardValue.SumValue > 14)
		{
			//ը����������ֱ��ը�������ǲ�ֺ������Ϊ������
			for (int i = 3; i < 16; i++)
			{
				if (clsHandCardData.value_aHandCardList[i] == 4)
				{
					clsHandCardData.value_nPutCardList.push_back(i);
					clsHandCardData.value_nPutCardList.push_back(i);
					clsHandCardData.value_nPutCardList.push_back(i);
					clsHandCardData.value_nPutCardList.push_back(i);

					clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgBOMB_CARD, i, 4);

					return;
				}
			}
			//��ը
			if (clsHandCardData.value_aHandCardList[17] > 0 && clsHandCardData.value_aHandCardList[16] > 0)
			{

				clsHandCardData.value_nPutCardList.push_back(17);
				clsHandCardData.value_nPutCardList.push_back(16);

				clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgKING_CARD, 17, 2);

				return;
			}
		}
		//������Ϊ�����ƵĻ����ö���һ���ִΣ�����һ�֣�Ȩֵ����7�����ں����ĶԱȲο���
		BestHandCardValue.NeedRound += 1;
		//�ݴ���ѵ��ƺ�
		int BestMaxCard = 0;
		//˳����ȥ����
		int tmp_1 = 0;
		int tmp_2 = 0;
		//�Ƿ���Ƶı�־
		bool PutCards = false;
		//ͬΪ�Ĵ���
		for (int i = clsGameSituation.uctNowCardGroup.nMaxCard + 1; i < 16; i++)
		{
			if (clsHandCardData.value_aHandCardList[i] == 4)
			{
				for (int j = 3; j < 16; j++)
				{
					//��ѡ���������ϵ����Ҳ���ѡ�����ŵ��Ǹ���
					if (clsHandCardData.value_aHandCardList[j] > 1 && j != i)
					{
						//��ѡ���������ϵ����Ҳ���ѡ�����ŵ��Ǹ����Ҳ��ǵ�һ��ѡ�������ڸ���
						for (int k = j + 1; k < 16; k++)
						{
							if (clsHandCardData.value_aHandCardList[k] > 1 && k != i) 
							{
								clsHandCardData.value_aHandCardList[i] -= 4;
								clsHandCardData.value_aHandCardList[j] -= 2;
								clsHandCardData.value_aHandCardList[k] -= 2;
								clsHandCardData.nHandCardCount -= 8;
								HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
								clsHandCardData.value_aHandCardList[i] += 4;
								clsHandCardData.value_aHandCardList[j] += 2;
								clsHandCardData.value_aHandCardList[k] += 2;
								clsHandCardData.nHandCardCount += 8;

								//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��
								if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
								{
									BestHandCardValue = tmpHandCardValue;
									BestMaxCard = i;
									tmp_1 = j;
									tmp_2 = k;
									PutCards = true;
								}
							}
						}
					}
				}
			}
		}
		if (PutCards)
		{
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(BestMaxCard);
			clsHandCardData.value_nPutCardList.push_back(tmp_1);
			clsHandCardData.value_nPutCardList.push_back(tmp_1);
			clsHandCardData.value_nPutCardList.push_back(tmp_2);
			clsHandCardData.value_nPutCardList.push_back(tmp_2);
			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgFOUR_TAKE_TWO, BestMaxCard, 8);
			return;
		}
        //����������Ȩֵ��С���������û��ѡ������õ��Ĵ������ͣ���ôҲҪը����Ϊ������
		for (int i = 3; i < 16; i++)
		{
			if (clsHandCardData.value_aHandCardList[i] == 4)
			{
				clsHandCardData.value_nPutCardList.push_back(i);
				clsHandCardData.value_nPutCardList.push_back(i);
				clsHandCardData.value_nPutCardList.push_back(i);
				clsHandCardData.value_nPutCardList.push_back(i);

				clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgBOMB_CARD, i, 4);

				return;
			}
		}
		//��ը
		if (clsHandCardData.value_aHandCardList[17] > 0 && clsHandCardData.value_aHandCardList[16] > 0)
		{

			clsHandCardData.value_nPutCardList.push_back(17);
			clsHandCardData.value_nPutCardList.push_back(16);

			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgKING_CARD, 17, 2);

			return;
		}
		//�ܲ���
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;

	}
	//ը������ 
	else if (clsGameSituation.uctNowCardGroup.cgType == cgBOMB_CARD)
	{
		//�����ը����������ֱ��ը�������ǲ�ֺ������Ϊ������
		for (int i = clsGameSituation.uctNowCardGroup.nMaxCard + 1; i < 16; i++)
		{
			if (clsHandCardData.value_aHandCardList[i] == 4)
			{
				clsHandCardData.value_nPutCardList.push_back(i);
				clsHandCardData.value_nPutCardList.push_back(i);
				clsHandCardData.value_nPutCardList.push_back(i);
				clsHandCardData.value_nPutCardList.push_back(i);

				clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgBOMB_CARD, i, 4);

				return;
			}
		}
		//��ը
		if (clsHandCardData.value_aHandCardList[17] > 0 && clsHandCardData.value_aHandCardList[16] > 0)
		{

			clsHandCardData.value_nPutCardList.push_back(17);
			clsHandCardData.value_nPutCardList.push_back(16);

			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgKING_CARD, 17, 2);

			return;
		}
		//�ܲ���
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
		
	}
	//��ը���� �˶���ը���㻹����ë
	else if (clsGameSituation.uctNowCardGroup.cgType == cgKING_CARD)
	{
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//�쳣���� ����
	else
	{
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
	}
	return;
}

/*
2.0�汾����  ���ݳ������ƾ�����ǰԤ��������ơ�����������
*/
void get_PutCardList_2_unlimit(GameSituation &clsGameSituation, HandCardData &clsHandCardData)
{
	//2.0�汾��ʱֻ��������������������
	get_PutCardList_2(clsHandCardData);

	clsGameSituation.uctNowCardGroup = clsHandCardData.uctPutCardType;
}
