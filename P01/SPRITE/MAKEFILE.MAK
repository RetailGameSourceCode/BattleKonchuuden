battle.tex:
	timpos light.tim    960   0   0 496
	timpos at.tim       832   0 256 490
	timpos fix.tim      832 368 256 480
	timpos efect1.tim   832  72 272 480
	timpos renda.tim    832 152 288 481
	timpos golight.tim  832 256 288 480
	timpos ap2.tim      832 288 288 484
	timpos vs.tim       840 256 304 494
	timpos nizi.tim     832 232   0 509
	timpos ha.tim       852 256 288 495
	timpos syouri.tim   768 256 256 488
	timpos sun.tim      848   0 304 480
	timpos f01.tim      860 256 304 481
	timpos f02.tim      876 256 304 482
	timpos f03.tim      880 256 304 483
	timpos f04.tim      868 256 304 484
	timpos f05.tim      864   0 304 485
	timpos f06.tim      882 256 304 487
	timpos f07.tim      884 256 304 486
	timpos bomefect.tim 896  96 288 494
	timpos beem.tim     880   0 304 488
	timpos beem2.tim    768 328 304 489
	timpos beem3.tim    886 256 304 490
	timpos syamei.tim   896 256   0 507
	timpos titles.tim   896 288   0 508
	cmplz light.tim light.lz
	cmplz at.tim at.lz
	cmplz fix.tim fix.lz
	cmplz efect1.tim efect1.lz
	cmplz renda.tim renda.lz
	cmplz golight.tim golight.lz
	cmplz ap2.tim ap2.lz
	cmplz vs.tim vs.lz
	cmplz nizi.tim nizi.lz
	cmplz ha.tim ha.lz
	cmplz syouri.tim syouri.lz
	cmplz sun.tim sun.lz
	cmplz f01.tim f01.lz
	cmplz f02.tim f02.lz
	cmplz f03.tim f03.lz
	cmplz f04.tim f04.lz
	cmplz f05.tim f05.lz
	cmplz f06.tim f06.lz
	cmplz f07.tim f07.lz
	cmplz bomefect.tim bomefect.lz
	cmplz beem.tim beem.lz
	cmplz beem2.tim beem2.lz
	cmplz beem3.tim beem3.lz
	cmplz syamei.tim syamei.lz
	cmplz titles.tim titles.lz
	hdlink /n /l battle.lis
	copy battle.tex d:\98025\dt
	del *.lz

efect1.c: efect1.anm
	anm2c -u   0  72 -s efe1 efect1.anm

renda.c: renda.anm
	anm2c -u   0 152 -s ren renda.anm

golight.c: golight.anm
	anm2c -u   0   0 -s gol golight.anm

ap2.c: ap2.anm
	anm2c -u   0 288 -s ap2 ap2.anm

nizi.c: nizi.anm
	anm2c -u   0 232 -s nizi nizi.anm

vs.c: vs.anm
	anm2c -u  16   0 -s vs vs.anm

syouri.c: syouri.anm
	anm2c -u   0   0 -s syo syouri.anm

beem3.c: beem3.anm
	anm2c -u 886 256 -s bem3 beem3.anm

fix.c: fix.anm
	anm2c -u   0 368 -s fix fix.anm

