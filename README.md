# ExplainerLibraries

### How to add a new explainer to the catalog

**1)**	In order to add a new explainer, you have to create a new Resource. First, go to the resources folder and select the folder corresponding to the data type of the explainer you want to add (If your explainer works with a different data type, please add the corresponding folder to the resources folder). For illustration purposes, we will add a new explainer, LIME tabular.

**2)**	Inside the appropriate folder, *create a new .py file* with the name of your explainer. In our case, inside /resources/tabular/ we create the lime.py file.

**3)**	Create a class for the explainer that represents a resource. This class needs to have *two different methods: post and get*. In our example:

```python
from flask_restful import Resource

class Lime(Resource):

	def post(self):
		return {}
		
	def get(self):
		return {}
```
**4)**	In the post method, define the mandatory arguments that must be passed for the explainer to get an explanation. In most explainers, this includes the files for the model and data (when needed), and an additional argument called params, which is a dictionary containing parameters such as a particular instance for local methods, configuration options, and additional information needed by the explainer. Note in the example that after parsing the arguments, we use joblib to load the file parameters since the model and data are passed as pickled files.

```python	
class Lime(Resource):

def post(self):
        parser = reqparse.RequestParser()
        parser.add_argument("model", type=werkzeug.datastructures.FileStorage, location='files')
        parser.add_argument("data", type=werkzeug.datastructures.FileStorage, location='files')
        parser.add_argument('params')
        args = parser.parse_args()
        
        data = args.get("data")
        model = args.get("model")
        dataframe = joblib.load(data)
        params_json = json.loads(args.get("params"))
        instance=params_json["instance"]
        backend = params_json["backend"]

	...
```
**5)** Add the actual code for the generation of the explanation to the poste method. **Note:** currently we return a json containing the values of a certain explanation. This json will also contain a URL to download a plot or image of the explanation when applicable.

