.PHONY: build

dev := $(or $(dev), 'false')

ifneq (,$(wildcard .env))
include .env
export
endif

.PHONY: help
.DEFAULT_GOAL := help
help:
	@grep -h -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

.PHONY: prepare
prepare: ## Install prerequisites
ifeq (,$(wildcard $(shell pwd)/build))
	@mkdir $(shell pwd)/build
endif

.PHONY: build
build: prepare ## Build the project
	@cd $(shell pwd)/build && cmake .. && make