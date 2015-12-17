Install prerequisites:

		conda create -c inria-pro-sed -n numini yaml-cpp boost waf
		source activate numini

Configure and build:

		waf configure --use-config=dev
		waf build
