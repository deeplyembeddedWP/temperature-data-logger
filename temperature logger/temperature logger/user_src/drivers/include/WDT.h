/*
 * WDT.h
 *
 * Created: 30/06/2024 4:58:01 pm
 * Author: Vinay Divakar
 * Brief: WDT to fire if lockup occurs
 */ 


#ifndef WDT_H_
#define WDT_H_

void WDT_init(void);
void WDT_feed(void);

#endif /* WDT_H_ */