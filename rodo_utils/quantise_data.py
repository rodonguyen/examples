#%%
import pandas
import os

filepath = '../data/test.csv'
df = pandas.read_csv(filepath, header=None)


def quantise(df: pandas.DataFrame):
   subdf = df.iloc[:,1:] / (256/8)
   subdf = subdf.astype(int)
   # subdf.info()

   df.iloc[:,1:] = subdf
   # print(df)

   return df


# quantise(df)




#%%
dirs = [
   '../data/', 
   '../data/mnist_train_split/'
   ]

for path in dirs:
   for file in sorted(os.listdir(path)):
      full_file_path = path + file
      if 'mnist' not in full_file_path \
         or '.csv' not in full_file_path \
         or '_q' in full_file_path \
         or '128' not in full_file_path:
         continue

      print(full_file_path)
      df = pandas.read_csv(full_file_path, header=None)
      df = quantise(df)
      df.to_csv(full_file_path[:-4] + '_q.csv', header=None, index=None)






# %%
