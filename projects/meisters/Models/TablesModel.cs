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

        public void StepIntoTable(int id)
        {
            if (id >= 0 && id < TablesData.Tables.Length)
            {
                // TODO::YARON - Update this logic
                TablesData.IsReservationOpen = true;
                TablesData.CurrentTable = id;

                if (TablesData.Tables[id].Status == ETableStatus.Clear)
                {
                    TablesData.Tables[id].Status = ETableStatus.NoOrder;
                    TablesData.Tables[id].TotalStopwatch.Start();
                    TablesData.Tables[id].StatusStopwatch.Start();
                }

                TablesData.RaiseTablesPropertyChanged();
            }
        }
    }
}
