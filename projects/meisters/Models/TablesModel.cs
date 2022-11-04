using Meisters.Data;
using Meisters.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Meisters.Models
{
    public class TablesModel
    {
        public TablesModel()
        {
            for (int idx = 0; idx < TablesData.Tables.Length; ++idx)
            {
                TablesData.Tables[idx] = new Table(idx);
            }
        }

        public TablesData TablesData { get; } = new TablesData();
        public event EventHandler UpdateDinersNum;

        public void StepIntoTable(int id)
        {
            if (id >= 0 && id < TablesData.Tables.Length)
            {
                // TODO::YARON - Update this logic
                TablesData.IsReservationOpen = true;
                TablesData.CurrentTable = TablesData.Tables[id];

                if (TablesData.CurrentTable.Status == ETableStatus.Clear)
                {
                    TablesData.CurrentTable.Status = ETableStatus.NoOrder;
                    TablesData.CurrentTable.TotalStopwatch.Start();
                    TablesData.CurrentTable.StatusStopwatch.Start();

                    UpdateDinersNum?.Invoke(this, EventArgs.Empty);
                }
            }
        }

        public void UpdateTableDinersNum(int id, uint dinersNum)
        {
            if (id >= 0 && id < TablesData.Tables.Length)
            {
                TablesData.Tables[id].DinersNum = dinersNum;
            }
        }

        public void OrderProduct(Product product)
        {
            TablesData.CurrentTable.Order.Add(new Product(product));
        }

        public void SendReservation()
        {
            var currTable = TablesData.CurrentTable;
            foreach (var product in currTable.Order)
            {
                product.SentToKitchen = true;
            }

            if (currTable.Status == ETableStatus.NoOrder && currTable.Order.Count != 0)
            {
                currTable.Status = ETableStatus.Order;
            }
        }
    }
}
