ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
SPIRIT_DIR=boss\rsd

all : sp.mot sp1.mod sp2.mod
    psymake

sp1.mod: $(SPIRIT_DIR)\sp1.lz
	hdlink /n /l sp1.lis

$(SPIRIT_DIR)\sp1.lz:
	cd $(SPIRIT_DIR)
	timpos $(TIM_DIR)/me.tim      384   0   0 480
	timpos $(TIM_DIR)/hara4.tim   384  48  16 482
	timpos $(TIM_DIR)/head.tim    416  64  32 482
	timpos $(TIM_DIR)/skin.tim    432   0  48 482
	timpos $(TIM_DIR)/body.tim    448   0  64 482
	timpos $(TIM_DIR)/body(s).tim 480   0  80 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name54.tim     896   0   0 487
	timpos $(NAMEVS)/namevs54.tim 896  16  16 487
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/skin.tim    skin.lz
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/body(s).tim body(s).lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name54.tim     name.lz
	cmplz $(NAMEVS)/namevs54.tim namevs.lz
	hdlink /n /l ..\..\sp1t.lis
	rsdlink boss.arg
	tmdsort -o sp1.tmd a.tmd
	cmplz sp1.tmd sp1.lz
	del a.tmd
	cd ..\..

sp2.mod: $(SPIRIT_DIR)\sp2.lz
	hdlink /n /l sp2.lis

$(SPIRIT_DIR)\sp2.lz:
	cd $(SPIRIT_DIR)
	timpos $(TIM_DIR)/me.tim      640   0   0 488
	timpos $(TIM_DIR)/hara4.tim   640  48  16 490
	timpos $(TIM_DIR)/head.tim    672  64  32 490
	timpos $(TIM_DIR)/skin.tim    688   0  48 490
	timpos $(TIM_DIR)/body.tim    704   0  64 490
	timpos $(TIM_DIR)/body(s).tim 736   0  80 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name54.tim     926   0   0 495
	timpos $(NAMEVS)/namevs54.tim 896  56  16 495
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/skin.tim    skin.lz
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/body(s).tim body(s).lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name54.tim     name.lz
	cmplz $(NAMEVS)/namevs54.tim namevs.lz
	hdlink /n /l ..\..\sp2t.lis
	rsdlink boss.arg
	tmdsort -o sp2.tmd a.tmd
	cmplz sp2.tmd sp2.lz
	del a.tmd
	cd ..\..

sp.mot: $(SPIRIT_DIR)\$(ANM_DIR)/bossiki.lz \
		$(SPIRIT_DIR)\$(ANM_DIR)/boscom0.lz \
		$(SPIRIT_DIR)\$(ANM_DIR)/boscom0m.lz \
		$(SPIRIT_DIR)\$(ANM_DIR)/boscom1.lz \
		$(SPIRIT_DIR)\$(ANM_DIR)/boscom1m.lz \
		$(SPIRIT_DIR)\$(ANM_DIR)/boscom2.lz \
		$(SPIRIT_DIR)\$(ANM_DIR)/boscom2m.lz \
		$(SPIRIT_DIR)\$(ANM_DIR)/bosatc1.lz \
		$(SPIRIT_DIR)\$(ANM_DIR)/bosatc2.lz \
		$(SPIRIT_DIR)\$(ANM_DIR)/bosido0.lz \
		$(SPIRIT_DIR)\$(ANM_DIR)/bosido1.lz \
		$(SPIRIT_DIR)\$(ANM_DIR)/boschag.lz \
		$(SPIRIT_DIR)\$(ANM_DIR)/bosdm0.lz \
		$(SPIRIT_DIR)\$(ANM_DIR)/bosdm0m.lz \
		$(SPIRIT_DIR)\$(ANM_DIR)/bosdm1.lz \
		$(SPIRIT_DIR)\$(ANM_DIR)/bosdm1m.lz \
		$(SPIRIT_DIR)\$(ANM_DIR)/bosdm2.lz \
		$(SPIRIT_DIR)\$(ANM_DIR)/bosdm2m.lz \
		$(SPIRIT_DIR)\$(ANM_DIR)/bosftb0.lz \
		$(SPIRIT_DIR)\$(ANM_DIR)/bosftb1.lz \
		$(SPIRIT_DIR)\$(ANM_DIR)/hm_bos.lz \
		$(SPIRIT_DIR)\$(ANM_DIR)/bosbks.lz \
		$(SPIRIT_DIR)\$(ANM_DIR)/bosstos0.lz \
		$(SPIRIT_DIR)\$(ANM_DIR)/bosstos1.lz \
		$(SPIRIT_DIR)\$(ANM_DIR)/bosstos2.lz \
		$(SPIRIT_DIR)\$(ANM_DIR)/54uke.lz
	hdlink /n /l sp.lis

$(SPIRIT_DIR)\$(ANM_DIR)/bossiki.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn bossiki
	cmplz bossiki.mtn bossiki.lz
	cd ..\..

$(SPIRIT_DIR)\$(ANM_DIR)/boscom0.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn boscom0
	cmplz boscom0.mtn boscom0.lz
	cd ..\..

$(SPIRIT_DIR)\$(ANM_DIR)/boscom0m.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn boscom0m
	cmplz boscom0m.mtn boscom0m.lz
	cd ..\..

$(SPIRIT_DIR)\$(ANM_DIR)/boscom1.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn boscom1
	cmplz boscom1.mtn boscom1.lz
	cd ..\..

$(SPIRIT_DIR)\$(ANM_DIR)/boscom1m.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn boscom1m
	cmplz boscom1m.mtn boscom1m.lz
	cd ..\..

$(SPIRIT_DIR)\$(ANM_DIR)/boscom2.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn boscom2
	cmplz boscom2.mtn boscom2.lz
	cd ..\..

$(SPIRIT_DIR)\$(ANM_DIR)/boscom2m.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn boscom2m
	cmplz boscom2m.mtn boscom2m.lz
	cd ..\..

$(SPIRIT_DIR)\$(ANM_DIR)/bosatc1.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn bosatc1
	cmplz bosatc1.mtn bosatc1.lz
	cd ..\..

$(SPIRIT_DIR)\$(ANM_DIR)/bosatc2.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn bosatc2
	cmplz bosatc2.mtn bosatc2.lz
	cd ..\..

$(SPIRIT_DIR)\$(ANM_DIR)/bosido0.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn bosido0
	cmplz bosido0.mtn bosido0.lz
	cd ..\..

$(SPIRIT_DIR)\$(ANM_DIR)/bosido1.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn bosido1
	cmplz bosido1.mtn bosido1.lz
	cd ..\..

$(SPIRIT_DIR)\$(ANM_DIR)/bosbks.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn bosbks
	cmplz bosbks.mtn bosbks.lz
	cd ..\..

$(SPIRIT_DIR)\$(ANM_DIR)/boschag.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn boschag
	cmplz boschag.mtn boschag.lz
	cd ..\..

$(SPIRIT_DIR)\$(ANM_DIR)/bosdm0.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn bosdm0
	cmplz bosdm0.mtn bosdm0.lz
	cd ..\..

$(SPIRIT_DIR)\$(ANM_DIR)/bosdm0m.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn bosdm0m
	cmplz bosdm0m.mtn bosdm0m.lz
	cd ..\..

$(SPIRIT_DIR)\$(ANM_DIR)/bosdm1.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn bosdm1
	cmplz bosdm1.mtn bosdm1.lz
	cd ..\..

$(SPIRIT_DIR)\$(ANM_DIR)/bosdm1m.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn bosdm1m
	cmplz bosdm1m.mtn bosdm1m.lz
	cd ..\..

$(SPIRIT_DIR)\$(ANM_DIR)/bosdm2.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn bosdm2
	cmplz bosdm2.mtn bosdm2.lz
	cd ..\..

$(SPIRIT_DIR)\$(ANM_DIR)/bosdm2m.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn bosdm2m
	cmplz bosdm2m.mtn bosdm2m.lz
	cd ..\..

$(SPIRIT_DIR)\$(ANM_DIR)/bosftb0.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn bosftb0
	cmplz bosftb0.mtn bosftb0.lz
	cd ..\..

$(SPIRIT_DIR)\$(ANM_DIR)/bosftb1.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn bosftb1
	cmplz bosftb1.mtn bosftb1.lz
	cd ..\..

$(SPIRIT_DIR)\$(ANM_DIR)/hm_bos.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn hm_bos
	cmplz hm_bos.mtn hm_bos.lz
	cd ..\..

$(SPIRIT_DIR)\$(ANM_DIR)/54uke.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn 54uke
	cmplz 54uke.mtn 54uke.lz
	cd ..\..

$(SPIRIT_DIR)\$(ANM_DIR)/bosstos0.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn bosstos0
	cmplz bosstos0.mtn bosstos0.lz
	cd ..\..

$(SPIRIT_DIR)\$(ANM_DIR)/bosstos1.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn bosstos1
	cmplz bosstos1.mtn bosstos1.lz
	cd ..\..

$(SPIRIT_DIR)\$(ANM_DIR)/bosstos2.lz:
	cd $(SPIRIT_DIR)\$(ANM_DIR)
	bin2mtn bosstos2
	cmplz bosstos2.mtn bosstos2.lz
	cd ..\..


