all : framework_spec.html framework_spec.pdf sensorlib_spec.html sensorlib_spec.pdf 

framework_spec.pdf : framework_spec.adoc framework_theme.yml
	asciidoctor-pdf -r asciidoctor-diagram -r asciidoctor-mathematical -o $@ framework_spec.adoc
	$(RM) diag-*.svg

framework_spec.html : framework_spec.adoc
	asciidoctor -r asciidoctor-diagram -r asciidoctor-mathematical -o $@ framework_spec.adoc
	$(RM) diag-*.svg

sensorlib_spec.pdf : sensorlib_spec.adoc sensorlib_theme.yml
	asciidoctor-pdf -r asciidoctor-diagram -r asciidoctor-mathematical -o $@ sensorlib_spec.adoc
	$(RM) diag-*.svg

sensorlib_spec.html : sensorlib_spec.adoc
	asciidoctor -r asciidoctor-diagram -r asciidoctor-mathematical -o $@ sensorlib_spec.adoc
	$(RM) diag-*.svg

clean :
	$(RM) framework_spec.pdf
	$(RM) framework_spec.html
	$(RM) sensorlib_spec.pdf
	$(RM) sensorlib_spec.html
	$(RM) diag-*.svg stem-*.svg
	$(RM) -r .asciidoctor
