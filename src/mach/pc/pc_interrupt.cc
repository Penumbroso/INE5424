// EPOS PC Interrupt Dispatcher

#include <mach/pc/ic.h>

__BEGIN_SYS

void PC_IC::int_dispatch()
{
    // id must be static because we don't have a stack frame
    static int id; 

    ASM("	.align 16					\n"
        "	movl	$0, %0				\n"
        "	jmp	.L1					    \n"
        "	.align 16					\n"
        "	movl	$1, %0				\n"
        "	jmp	.L1					    \n"
        "	.align 16					\n"
        "	movl	$2, %0				\n"
        "	jmp	.L1				    	\n"
        "	.align 16					\n"
        "	movl	$3, %0				\n"
        "	jmp	.L1					    \n"
        "	.align 16					\n"
        "	movl	$4, %0				\n"
        "	jmp	.L1					    \n"
        "	.align 16					\n"
        "	movl	$5, %0				\n"
        "	jmp	.L1				    	\n"
        "	.align 16					\n"
        "	movl	$6, %0				\n"
        "	jmp	.L1					    \n"
        "	.align 16					\n"
        "	movl	$7, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$8, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$9, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$10, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$11, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$12, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$13, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$14, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$15, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$16, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$17, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$18, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$19, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$20, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$21, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$22, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$23, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$24, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$25, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$26, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$27, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$28, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$29, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$30, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$31, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$32, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$33, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$34, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$35, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$36, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$37, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$38, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$39, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$40, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$41, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$42, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$43, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$44, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$45, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$46, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$47, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$48, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$49, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$50, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$51, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$52, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$53, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$54, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$55, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$56, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$57, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$58, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$59, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$60, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$61, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$62, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$63, %0				\n"
        "	jmp	.L1						\n"
        "	.align 16					\n"
        "	movl	$64, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$65, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$66, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$67, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$68, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$69, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$70, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$71, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$72, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$73, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$74, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$75, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$76, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$77, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$78, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$79, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$80, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$81, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$82, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$83, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$84, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$85, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$86, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$87, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$88, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$89, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$90, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$91, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$92, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$93, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$94, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$95, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$96, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$97, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$98, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$99, %0				\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$100, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$101, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$102, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$103, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$104, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$105, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$106, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$107, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$108, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$109, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$110, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$111, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$112, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$113, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$114, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$115, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$116, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$117, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$118, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$119, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$120, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$121, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$122, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$123, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$124, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$125, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$126, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$127, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$128, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$129, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$130, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$131, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$132, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$133, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$134, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$135, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$136, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$137, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$138, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$139, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$140, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$141, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$142, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$143, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$144, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$145, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$146, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$147, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$148, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$149, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$150, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$151, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$152, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$153, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$154, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$155, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$156, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$157, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$158, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$159, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$160, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$161, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$162, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$163, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$164, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$165, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$166, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$167, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$168, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$169, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$170, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$171, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$172, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$173, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$174, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$175, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$176, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$177, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$178, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$179, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$180, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$181, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$182, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$183, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$184, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$185, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$186, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$187, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$188, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$189, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$190, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$191, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$192, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$193, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$194, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$195, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$196, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$197, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$198, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$199, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$200, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$201, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$202, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$203, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$204, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$205, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$206, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$207, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$208, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$209, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$210, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$211, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$212, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$213, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$214, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$215, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$216, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$217, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$218, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$219, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$220, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$221, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$222, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$223, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$224, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$225, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$226, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$227, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$228, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$229, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$230, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$231, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$232, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$233, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$234, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$235, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$236, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$237, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$238, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$239, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$240, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$241, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$242, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$243, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$244, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$245, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$246, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$247, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$248, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$249, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$250, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$251, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$252, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$253, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$254, %0			\n"
        // 	"	jmp	.L1						\n"
        // 	"	.align 16					\n"
        // 	"	movl	$255, %0			\n"
        ".L1:							\n"
        "	pushal						\n"
        : : "m"(id));

    ASM("	call	*%2					\n"
        "	movl    %0, %%eax			\n"
        "	pushl   %%eax				\n"
        "	call    *%1(,%%eax,4)		\n"
        "	popl	%%eax				\n"
        "	popal						\n"
        "	iret						\n"
        : : "m"(id), "m"(_int_vector[0]), "r"(PC_IC::eoi));
}

__END_SYS
