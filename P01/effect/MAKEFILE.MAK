all :
	rsdlink tukibom.rsd
	tmdsort -o tukibom.tmd a.tmd
	rsdlink tukibom2.rsd
	tmdsort -o tukibom2.tmd a.tmd

	timpos beem.tim     880   0 304 488
	timpos beem2.tim    768 328 304 489
	rsdlink beemd.rsd
	tmdsort -o beemd.tmd a.tmd
	rsdlink beem2.rsd
	tmdsort -o beem2.tmd a.tmd
	rsdlink beemmax.rsd
	tmdsort -o beemmax.tmd a.tmd
	rsdlink beem2max.rsd
	tmdsort -o beem2max.tmd a.tmd
	rsdlink beemmid.rsd
	tmdsort -o beemmid.tmd a.tmd
	rsdlink beem2mid.rsd
	tmdsort -o beem2mid.tmd a.tmd
	rsdlink beemwa.rsd
	tmdsort -o beemwa.tmd a.tmd

	timpos beem.tim     880   0 304 491
	timpos beem2.tim    768 328 304 492
	rsdlink beemd.rsd
	tmdsort -o ceemd.tmd a.tmd
	rsdlink beem2.rsd
	tmdsort -o ceem2.tmd a.tmd
	rsdlink beemmax.rsd
	tmdsort -o ceemmax.tmd a.tmd
	rsdlink beem2max.rsd
	tmdsort -o ceem2max.tmd a.tmd
	rsdlink beemmid.rsd
	tmdsort -o ceemmid.tmd a.tmd
	rsdlink beem2mid.rsd
	tmdsort -o ceem2mid.tmd a.tmd
	rsdlink beemwa.rsd
	tmdsort -o ceemwa.tmd a.tmd

	rsdlink beemtama.rsd
	tmdsort -o beemtama.tmd a.tmd
	rsdlink needle.rsd
	tmdsort -o needle.tmd a.tmd
	hdlink /n /l efe.lis
	cmplz efe.mod efe.lz
	copy efe.lz d:\98025\dt
	del a.tmd

