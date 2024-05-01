#ifndef BIT_MATH_H
#define BIT_MATH_H
#define SET_BIT(Reg,BIT) Reg|=(1<<BIT)

#define Toggle_BIT(Reg,BIT) Reg^=(1<<BIT)

#define GET_BIT(Reg,BIT) (Reg>>BIT)&(1)

#define CLR_BIT(Reg,BIT) Reg&=(~(1<<BIT))

#endif