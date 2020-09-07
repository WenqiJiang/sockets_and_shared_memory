# sockets_and_shared_memory

## IPC Performance Test --- Unix Domain Socket

All experiments transfer 10 GB data.

* Packet = 1K, 10 GB

Time spent on client side: 21.90720295906067 seconds

Throughput = 0.4564708702743847 GB/s

* Packet = 10K, 10 GB

Time spent on client side: 10.377486944198608 seconds

Throughput = 0.963624435643387 GB/s

* Packet = 100K, 10 GB

Time spent on client side: 6.494897127151489 seconds

Throughput = 1.5396614578754317 GB/s

* Packet = 1M, 10 GB

Time spent on client side: 6.0761847496032715 seconds

Throughput = 1.6457695761559792 GB/s

* Packet = 10M, 10 GB

Time spent on client side: 7.021316051483154 seconds

Throughput = 1.4242344208230935 GB/s



## Install Boost

* Download tar.gz on https://www.boost.org/
* Follow section 5.1 https://www.boost.org/doc/libs/1_66_0/more/getting_started/unix-variants.html#easy-build-and-install
  * step 2 don't add prefix, it will install to /usr/local, where lib and include file are installed to /usr/local/lib and /usr/local/include