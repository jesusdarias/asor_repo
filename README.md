# ExplainerLibraries

### How to add a new explainer to the catalog

1)	In order to add a new explainer, you have to create a new Resource. First, go to the resources folder and select the folder corresponding to the data type of the explainer you want to add (If your explainer works with a different data type, please add the corresponding folder to the resources folder). For illustration purposes, we will add a new explainer, LIME tabular.

2)	Inside the appropriate folder, *create a new .py file* with the name of your explainer. In our case, inside /resources/tabular/ we create the lime.py file.

3)	Create a class for the explainer that represents a resource. This class needs to have *two different methods: post and get*. In our example:

```
from flask_restful import Resource
class Lime(Resource):
	def post(self):
		return {}
	def get(self):
		return {}
```
