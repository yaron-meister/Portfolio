using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.Net.Http;
using Newtonsoft.Json;

namespace BreakingNewsApp
{
    class NewsServer
    {
        public async ValueTask<News> GetNews()
        {
            try
            {
                string NEWS_API_KEY = Environment.GetEnvironmentVariable("NewsApiKey");
                string response =
                    await client.GetStringAsync($"https://newsapi.org/v2/top-headlines?country=us&apiKey={NEWS_API_KEY}");
                news = JsonConvert.DeserializeObject<News>(response);
            }
            catch (Exception exception)
            {
                news.status = "Fail";
                Console.WriteLine("NewsServer: Request/Convert exception: " + exception);
            }

            return (news);
        }

        public class News
        {
            // Properties
            public string status { get; set; }
            public int totalResults { get; set; }
            public List<Article> articles { get; set; }
        }

        public class Article
        {
            public class Source
            {
                // Properties
                public string id { get; set; }
                public string name { get; set; }
            }

            // Properties
            public Source source { get; set; }
            public string author { get; set; }
            public string title { get; set; }
            public string description { get; set; }
            public string url { get; set; }
            public string imageUrl { get; set; }
            public string publishedAt { get; set; }
            public string content { get; set; }
        }

        // Members
        News news = new News();
        HttpClient client = new HttpClient();
    }
}
