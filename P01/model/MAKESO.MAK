ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
OOKUWA_DIR=59\rsd
OKTOBI=59tob\rsd

all : so1.mod so2.mod
    psymake

so1.mod: $(OOKUWA_DIR)\so1.lz $(OKTOBI)\sotob1.lz
	hdlink /n /l so1.lis

$(OOKUWA_DIR)\so1.lz:
	cd $(OOKUWA_DIR)
	timpos $(TIM_DIR)/beta.tim    448   0  16 482
	timpos $(TIM_DIR)/beta2.tim   448   8  32 482
	rsdlink ookw.arg
	tmdsort -o so1.tmd a.tmd
	cmplz so1.tmd so1.lz
	del a.tmd
	cd ..\..

$(OKTOBI)\sotob1.lz:
	cd $(OKTOBI)
	timpos $(TIM_DIR)/hane1.tim   428 192  96 482
	timpos $(TIM_DIR)/beta.tim    448   0  16 482
	timpos $(TIM_DIR)/beta2.tim   448   8  32 482
	timpos $(TIM_DIR)/hane2.tim   448 192 144 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name59.tim     896   0   0 487
	timpos $(NAMEVS)/namevs59.tim 896  16  16 487
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/beta.tim    beta.lz
	cmplz $(TIM_DIR)/beta2.tim   beta2.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name59.tim     name.lz
	cmplz $(NAMEVS)/namevs59.tim namevs.lz
	hdlink /n /l ..\..\so1t.lis
	rsdlink oktos.arg
	tmdsort -o sotob1.tmd a.tmd
	cmplz sotob1.tmd sotob1.lz
	del a.tmd
	cd ..\..

so2.mod: $(OOKUWA_DIR)\so2.lz $(OKTOBI)\sotob2.lz
	hdlink /n /l so2.lis

$(OOKUWA_DIR)\so2.lz:
	cd $(OOKUWA_DIR)
	timpos $(TIM_DIR)/beta.tim    704   0  16 490
	timpos $(TIM_DIR)/beta2.tim   704   8  32 490
	rsdlink ookw.arg
	tmdsort -o so2.tmd a.tmd
	cmplz so2.tmd so2.lz
	del a.tmd
	cd ..\..

$(OKTOBI)\sotob2.lz:
	cd $(OKTOBI)
	timpos $(TIM_DIR)/hane1.tim   684 192  96 490
	timpos $(TIM_DIR)/beta.tim    704   0  16 490
	timpos $(TIM_DIR)/beta2.tim   704   8  32 490
	timpos $(TIM_DIR)/hane2.tim   704 192 144 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name59.tim     926   0   0 495
	timpos $(NAMEVS)/namevs59.tim 896  56  16 495
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/beta.tim    beta.lz
	cmplz $(TIM_DIR)/beta2.tim   beta2.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name59.tim     name.lz
	cmplz $(NAMEVS)/namevs59.tim namevs.lz
	hdlink /n /l ..\..\so2t.lis
	rsdlink oktos.arg
	tmdsort -o sotob2.tmd a.tmd
	cmplz sotob2.tmd sotob2.lz
	del a.tmd
	cd ..\..

