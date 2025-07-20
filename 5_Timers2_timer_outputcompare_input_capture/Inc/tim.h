#ifndef TIM_H_
#define TIM_H_

#define SR_CC1IF			(1U << 1)

void tim1_pe9_output_compare(void);
void tim3_pa6_input_capture(void);

#endif /* TIM_H_ */
